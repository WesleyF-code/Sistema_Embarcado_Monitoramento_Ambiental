import matplotlib.pyplot as plt
import datetime

# ==========================================
# CONFIGURAÇÃO DO TEMPO
# LOG: 18:20h até 00:00h
# ==========================================

num_leituras = 15

inicio = datetime.datetime.strptime("18:20", "%H:%M")

tempos = [
    inicio + datetime.timedelta(
        minutes=i * ((5 * 60 + 40) / (num_leituras - 1))
    )
    for i in range(num_leituras)
]

tempos_str = [t.strftime("%H:%M") for t in tempos]

# ==========================================
# TEMPERATURA
# SUBSTITUA PELOS VALORES DO LOG
# ==========================================

temperatura = [
    30.5, 30.2, 29.9, 29.7, 29.4,
    29.1, 28.8, 28.6, 28.4, 28.2,
    28.0, 27.8, 27.6, 27.5, 27.4
]

plt.figure(figsize=(9,4.5))

plt.plot(
    tempos_str,
    temperatura,
    color='red',
    marker='o',
    linewidth=2
)

plt.title(
    'Variação de Temperatura (°C) - 18:20h às 00:00h',
    fontsize=12,
    fontweight='bold'
)

plt.xlabel('Horário da Leitura')
plt.ylabel('Temperatura (°C)')

plt.grid(True, linestyle='--')

plt.tight_layout()
plt.show()
