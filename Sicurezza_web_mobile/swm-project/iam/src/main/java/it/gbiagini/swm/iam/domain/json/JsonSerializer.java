package it.gbiagini.swm.iam.domain.json;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.SerializerProvider;
import com.fasterxml.jackson.databind.ser.std.StdSerializer;

import java.io.IOException;
import java.util.Objects;

public class JsonSerializer extends StdSerializer<String> {
    private static final long serialVersionUID = 1L;

    public JsonSerializer() {
        this(null);
    }

    public JsonSerializer(Class<String> t) {
        super(t);
    }


    @Override
    public void serialize(String s, JsonGenerator jsonGenerator, SerializerProvider serializerProvider) throws IOException {
        if (Objects.nonNull(s)) {
            jsonGenerator.writeRawValue(s);
        } else {
            jsonGenerator.writeNull();
        }
    }
}
