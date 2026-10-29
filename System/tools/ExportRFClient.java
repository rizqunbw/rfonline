// Run after Ghidra auto-analysis; this script never executes the target program.
// @category RFOnline
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.util.task.TaskMonitor;
import com.google.gson.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.zip.GZIPOutputStream;

public class ExportRFClient extends GhidraScript {
    private final Gson gson = new GsonBuilder().setPrettyPrinting().create();
    public void run() throws Exception {
        String[] args=getScriptArgs();
        if(args.length!=3) throw new IllegalArgumentException("outputDirectory inventoryJson scratchDirectory");
        Path out=Paths.get(args[0]),scratch=Paths.get(args[2]);
        Files.createDirectories(out);Files.createDirectories(scratch);
        FunctionManager fm=currentProgram.getFunctionManager();
        List<Function> functions=new ArrayList<>();
        for(Function f:fm.getFunctions(true)) if(!f.isExternal()) functions.add(f);
        JsonArray refs=new JsonArray();
        JsonObject inventory=JsonParser.parseString(Files.readString(Paths.get(args[1]))).getAsJsonObject();
        for(JsonElement element:inventory.getAsJsonArray("resource_references")) {
            JsonObject row=element.getAsJsonObject().deepCopy();JsonArray uses=new JsonArray();
            for(Reference r:currentProgram.getReferenceManager().getReferencesTo(toAddr(Long.decode(row.get("va").getAsString())))) {
                JsonObject use=new JsonObject();use.addProperty("instruction",r.getFromAddress().toString());use.addProperty("type",r.getReferenceType().toString());
                Function owner=fm.getFunctionContaining(r.getFromAddress());
                if(owner!=null){use.addProperty("function",owner.getEntryPoint().toString());use.addProperty("name",owner.getName());}
                uses.add(use);
            }
            row.add("references",uses);refs.add(row);
        }
        Files.writeString(out.resolve("resource-xrefs.json"),gson.toJson(refs)+"\n");
        println("RF_EXPORT functions="+functions.size()+" resourceReferences="+refs.size());
        // Make key paths reviewable before the full bulk export completes.
        Path selected=out.resolve("selected");Files.createDirectories(selected);
        long[] reviewAddresses={0x7bcf93L,0x5286a0L,0x732210L,0x821a88L,0x538d14L,0x539879L,0x539946L,0x539aabL,0x538e80L,0x538f50L,0x539020L,0x539ca0L,0x539d80L,0x5c4090L,0x5cb290L,0x88e160L};
        DecompInterface review=new DecompInterface();review.openProgram(currentProgram);
        try {
            for(long va:reviewAddresses) {
                Function f=fm.getFunctionContaining(toAddr(va));if(f==null)continue;
                DecompileResults result=review.decompileFunction(f,20,monitor);
                if(result.decompileCompleted() && result.getDecompiledFunction()!=null)
                    Files.writeString(selected.resolve(f.getEntryPoint().toString()+".c"),result.getDecompiledFunction().getC());
            }
        } finally {review.dispose();}
        AtomicInteger next=new AtomicInteger(),done=new AtomicInteger();
        JsonObject[] records=new JsonObject[functions.size()];
        ExecutorService pool=Executors.newFixedThreadPool(4);
        List<Future<?>> jobs=new ArrayList<>();
        for(int worker=0;worker<4;worker++) jobs.add(pool.submit(()->{
            DecompInterface decompiler=new DecompInterface();
            try {
                DecompileOptions options=new DecompileOptions();options.grabFromProgram(currentProgram);
                decompiler.setOptions(options);decompiler.toggleCCode(true);decompiler.toggleSyntaxTree(false);
                if(!decompiler.openProgram(currentProgram)) throw new IOException(decompiler.getLastMessage());
                for(int index;(index=next.getAndIncrement())<functions.size();) {
                    Function f=functions.get(index);String address=f.getEntryPoint().toString();
                    JsonObject row=new JsonObject();row.addProperty("address",address);row.addProperty("name",f.getName());row.addProperty("bytes",f.getBody().getNumAddresses());
                    row.addProperty("signature",f.getSignature().toString());
                    JsonArray calls=new JsonArray();for(Function callee:f.getCalledFunctions(TaskMonitor.DUMMY)) calls.add(callee.getEntryPoint().toString());row.add("calls",calls);
                    DecompileResults result=decompiler.decompileFunction(f,15,TaskMonitor.DUMMY);
                    boolean ok=result.decompileCompleted() && result.getDecompiledFunction()!=null;
                    row.addProperty("decompiled",ok);row.addProperty("message",result.getErrorMessage());
                    String code=ok?result.getDecompiledFunction().getC():"/* Decompilation unavailable; see functions.json. */\n";
                    Files.writeString(scratch.resolve(address+".c"),code);
                    records[index]=row;
                    int count=done.incrementAndGet();if(count%1000==0) println("RF_EXPORT completed="+count+"/"+functions.size());
                }
            } catch(Exception e) {throw new RuntimeException(e);} finally {decompiler.dispose();}
        }));
        pool.shutdown();for(Future<?> job:jobs)job.get();
        int success=0;long codeBytes=0;
        try(Writer writer=new OutputStreamWriter(new GZIPOutputStream(Files.newOutputStream(out.resolve("client-decompiled.c.gz"))),StandardCharsets.UTF_8)) {
            writer.write("/* Ghidra-generated pseudocode, NOT original source or a buildable browser client.\nInput SHA-256: "+inventory.get("sha256").getAsString()+" */\n");
            for(JsonObject row:records) {
                if(row.get("decompiled").getAsBoolean())success++;
                String code=Files.readString(scratch.resolve(row.get("address").getAsString()+".c"));
                writer.write("\n/* FUNCTION "+row.get("address").getAsString()+" */\n");writer.write(code);codeBytes+=code.length();
            }
        }
        Files.writeString(out.resolve("functions.json"),gson.toJson(records)+"\n");
        try(Writer writer=new OutputStreamWriter(new GZIPOutputStream(Files.newOutputStream(out.resolve("functions.json.gz"))),StandardCharsets.UTF_8)){gson.toJson(records,writer);}
        JsonObject summary=new JsonObject();summary.addProperty("binarySha256",inventory.get("sha256").getAsString());
        summary.addProperty("tool","Ghidra 12.2");summary.addProperty("language",currentProgram.getLanguageID().toString());
        summary.addProperty("compiler",currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        summary.addProperty("functionsDiscovered",functions.size());summary.addProperty("decompiled",success);summary.addProperty("failed",functions.size()-success);summary.addProperty("pseudocodeCharacters",codeBytes);
        summary.addProperty("scope","All non-external functions discovered by this analysis, not proof of complete code coverage or recovered behavior.");
        Files.writeString(out.resolve("summary.json"),gson.toJson(summary)+"\n");println("RF_EXPORT finished "+gson.toJson(summary));
    }
}
