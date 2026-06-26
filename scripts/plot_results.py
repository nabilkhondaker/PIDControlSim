import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../build/simulation_results.csv')

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# System Response
ax1.plot(df['Time'], df['Output'], label='System Output (y)', color='b', linewidth=2)
ax1.plot(df['Time'], df['Setpoint'], label='Setpoint (r)', color='r', linestyle='--')
ax1.set_ylabel('Amplitude')
ax1.set_title('Plant Response vs Setpoint')
ax1.grid(True)
ax1.legend()

# Control Effort
ax2.plot(df['Time'], df['Control'], label='Control Effort (u)', color='g')
ax2.set_ylabel('Voltage / Force')
ax2.set_xlabel('Time (s)')
ax2.set_title('Controller Output & Saturation')
ax2.grid(True)
ax2.legend()

plt.tight_layout()
plt.show()
