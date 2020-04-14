package it.gbiagini.swm.iam.domain.json;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.TreeNode;
import com.fasterxml.jackson.databind.DeserializationContext;

import java.io.IOException;

public class JsonDeserializer extends com.fasterxml.jackson.databind.JsonDeserializer<String> {
    @Override
    public String deserialize(JsonParser jsonParser, DeserializationContext deserializationContext) throws IOException, JsonProcessingException {
        TreeNode tree = jsonParser.getCodec().readTree(jsonParser);
        return tree.toString();

    }
}
