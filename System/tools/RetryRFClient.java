// Retry only incomplete functions after the bulk export; no target execution.
// @category RFOnline
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import com.google.gson.*;
import java.nio.file.*;

public class RetryRFClient extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();Path out=Paths.get(args[0]),scratch=Paths.get(args[1]);
        JsonArray index=JsonParser.parseString(Files.readString(out.resolve("functions.json"))).getAsJsonArray();
        JsonArray attempts=new JsonArray();DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
        try {
            for(JsonElement element:index) {
                JsonObject row=element.getAsJsonObject();if(row.get("decompiled").getAsBoolean())continue;
                String address=row.get("address").getAsString();Function f=getFunctionAt(toAddr(address));
                DecompileResults result=d.decompileFunction(f,60,monitor);
                JsonObject attempt=new JsonObject();attempt.addProperty("address",address);attempt.addProperty("timeoutSeconds",60);
                boolean ok=result.decompileCompleted() && result.getDecompiledFunction()!=null;
                attempt.addProperty("decompiled",ok);attempt.addProperty("message",result.getErrorMessage());
                if(ok)Files.writeString(scratch.resolve(address+".c"),result.getDecompiledFunction().getC());
                attempts.add(attempt);println("RF_RETRY "+attempt);
            }
        } finally {d.dispose();}
        Files.writeString(out.resolve("retries.json"),new GsonBuilder().setPrettyPrinting().create().toJson(attempts)+"\n");
    }
}
