import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 4 * np.pi, 1000)
plt.plot(x, np.sin(x))
plt.xlim(0, 4 * np.pi)
plt.xlabel('x')
plt.ylabel('sin(x)')
plt.savefig('sine-py.png', dpi=200, bbox_inches='tight')
