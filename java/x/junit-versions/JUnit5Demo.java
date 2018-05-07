import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class JUnit5Demo {
    @Test
    public void foo() {
        assertEquals(1 == 1, true);
    }

    @Test
    public void bar() {
        assertEquals(1 == 2, false);
    }
}
