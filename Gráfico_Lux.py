import matplotlib.pyplot as plt
import datetime

# ==========================================
# LUMINOSIDADE
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

luminosidade = [
    40, 30, 20, 15, 10,
    8, 6, 5, 5, 5,
    5, 5, 5, 5, 5
]

plt.figure(figsize=(9,4.5))

plt.plot(
    tempos_str,
    luminosidade,
    color='orange',
    marker='D',
    linewidth=2
)

plt.title(
    'Variação de Luminosidade (lux) - 18:20h às 00:00h',
    fontsize=12,
    fontweight='bold'
)

plt.xlabel('Horário da Leitura')
plt.ylabel('Luminosidade (lux)')

plt.grid(True, linestyle='--')

plt.tight_layout()
plt.show()
