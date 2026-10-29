// Static decompilation of Go application functions discovered in pclntab.
// @category RFOnline
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.util.task.TaskMonitor;
import com.google.gson.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.zip.GZIPOutputStream;

public class ExportGommo extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();
        Path input=Paths.get(args[0]),out=Paths.get(args[1]),scratch=Paths.get(args[2]);
        Files.createDirectories(out);Files.createDirectories(scratch);
        JsonArray targets=JsonParser.parseString(Files.readString(input)).getAsJsonArray();
        JsonObject[] records=new JsonObject[targets.size()];AtomicInteger next=new AtomicInteger(),done=new AtomicInteger();
        FunctionManager fm=currentProgram.getFunctionManager();
        int recoveredEntries=0;
        for(JsonElement element:targets) {
            String va=element.getAsJsonObject().get("address").getAsString();
            if(fm.getFunctionAt(toAddr(Long.decode(va)))==null) {
                disassemble(toAddr(Long.decode(va)));
                if(createFunction(toAddr(Long.decode(va)),null)!=null)recoveredEntries++;
            }
        }
        println("GOMMO_EXPORT requested="+targets.size()+" additionalEntriesFromPclntab="+recoveredEntries);
        ExecutorService pool=Executors.newFixedThreadPool(4);List<Future<?>> jobs=new ArrayList<>();
        for(int worker=0;worker<4;worker++)jobs.add(pool.submit(()->{
            DecompInterface decompiler=new DecompInterface();
            try {
                DecompileOptions options=new DecompileOptions();options.grabFromProgram(currentProgram);
                decompiler.setOptions(options);decompiler.toggleCCode(true);decompiler.toggleSyntaxTree(false);
                if(!decompiler.openProgram(currentProgram))throw new IOException(decompiler.getLastMessage());
                for(int i;(i=next.getAndIncrement())<targets.size();) {
                    JsonObject row=targets.get(i).getAsJsonObject().deepCopy();String va=row.get("address").getAsString();
                    Function f=fm.getFunctionAt(toAddr(Long.decode(va)));boolean ok=false;String code="";
                    if(f==null)row.addProperty("message","No function recognized at pclntab entry by this Ghidra analysis");
                    else {
                        DecompileResults result=decompiler.decompileFunction(f,15,TaskMonitor.DUMMY);
                        ok=result.decompileCompleted() && result.getDecompiledFunction()!=null;
                        row.addProperty("message",result.getErrorMessage());row.addProperty("ghidraName",f.getName());
                        if(ok)code=result.getDecompiledFunction().getC();
                    }
                    row.addProperty("decompiled",ok);records[i]=row;
                    Files.writeString(scratch.resolve(va+".c"),code);
                    int count=done.incrementAndGet();if(count%1000==0)println("GOMMO_EXPORT "+count+"/"+targets.size());
                }
            }catch(Exception e){throw new RuntimeException(e);}finally{decompiler.dispose();}
        }));
        pool.shutdown();for(Future<?> job:jobs)job.get();
        Gson gson=new GsonBuilder().setPrettyPrinting().create();int success=0;
        try(Writer writer=new OutputStreamWriter(new GZIPOutputStream(Files.newOutputStream(out.resolve("application-decompiled.c.gz"))),StandardCharsets.UTF_8)) {
            writer.write("/* Generated pseudocode of Gommo application functions. Not original Go source. */\n");
            for(JsonObject row:records) {
                String va=row.get("address").getAsString();
                writer.write("\n/* FUNCTION "+va+" "+row.get("name").getAsString().replace("*/","* /")+" */\n");
                if(row.get("decompiled").getAsBoolean()){success++;writer.write(Files.readString(scratch.resolve(va+".c")));}
                else writer.write("/* Decompilation unavailable; see decompilation-index.json.gz. */\n");
            }
        }
        try(Writer writer=new OutputStreamWriter(new GZIPOutputStream(Files.newOutputStream(out.resolve("decompilation-index.json.gz"))),StandardCharsets.UTF_8)){gson.toJson(records,writer);}
        JsonObject summary=new JsonObject();summary.addProperty("functionsRequested",targets.size());summary.addProperty("decompiled",success);summary.addProperty("failed",targets.size()-success);
        summary.addProperty("tool","Ghidra 12.2");summary.addProperty("scope","Application functions with gommo/ or main. names from Go pclntab; external dependencies are indexed separately, not exported here.");
        Files.writeString(out.resolve("decompilation-summary.json"),gson.toJson(summary)+"\n");println("GOMMO_EXPORT finished "+summary);
    }
}
