import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class JUnit4Demo {
    @Test
    public void foo() {
        assertEquals(1 == 1, true);
    }

    @Test
    public void bar() {
        assertEquals(1 == 2, false);
    }
}
