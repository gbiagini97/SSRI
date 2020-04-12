package it.gbiagini.swm.logging;

import java.time.Duration;
import java.time.Instant;

public final class LoggingHelper {

    private final Instant beginInstant;
    private final String name;

    private final LoggingTag tag;

    public enum LoggingTag {SERVICE, EXTERNAL_CALL, INITIALIZATION, SHUTDOWN}

    private LoggingHelper(LoggingTag tag, String name, Instant beginInstant) {

        super();
        this.beginInstant = beginInstant;
        this.name = name;
        this.tag = tag;
    }

    public static LoggingHelper begin(LoggingTag tag, String name) {
        return new LoggingHelper(tag, name, Instant.now());
    }

    public static LoggingHelper hasBegunAt(LoggingTag tag, String name, Instant beginInstant) {
        if (beginInstant.isAfter((Instant.now()))) {
            throw new IllegalArgumentException("Time travels are not implemented. For now at least.");
        }
        return new LoggingHelper(tag, name, beginInstant);
    }

    public String getBeginTag() {
        return String.format("BEGIN_%s - Name:%s", tag, name);
    }

    public String getEndTag() {
        return String.format("END_%s - Name:%s, TotalTime:%s", tag, name, Duration.between(beginInstant, Instant.now()).toMillis());
    }

    public String getNameTag() {
        return String.format("Name:%s", name);
    }

    public String getEndTagWithoutTotalTime() {
        return String.format("END_%s - Name:%s, TotalTime:-1", tag, name);
    }

    public Instant getBeginInstant() {
        return beginInstant;
    }

}
