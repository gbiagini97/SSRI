package it.gbiagini.swm.vault.operation;

import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.vault.core.VaultTemplate;
import org.springframework.vault.support.VaultResponse;

@Repository
public class VaultOperation {

    @Autowired
    private VaultTemplate vaultTemplate;

    public JSONObject getSecret(String path) {
        VaultResponse response = vaultTemplate.read("kv-v2/data/" + path);
        try {
            return new JSONObject(response != null ? response.getData() : null).getJSONObject("data");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return new JSONObject();
    }
}
