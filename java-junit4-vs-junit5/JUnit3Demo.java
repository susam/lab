import junit.framework.TestCase;
import junit.framework.Test;

public class JUnit3Demo extends TestCase {
    // In JUnit 3 it is necessary to begin method names with "test" to
    // be recognized as tests.
    public void testFoo() {
        assertEquals(1 == 1, true);
    }

    public void testBar() {
        assertEquals(1 == 2, false);
    }
}
