import matplotlib.pyplot as plt
import datetime

# ==========================================
# PRESSÃO ATMOSFÉRICA
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

pressao = [
    1009.1, 1009.2, 1009.2, 1009.3, 1009.3,
    1009.4, 1009.4, 1009.5, 1009.5, 1009.5,
    1009.6, 1009.6, 1009.7, 1009.7, 1009.7
]

plt.figure(figsize=(9,4.5))

plt.plot(
    tempos_str,
    pressao,
    color='green',
    marker='^',
    linewidth=2
)

plt.title(
    'Variação de Pressão Atmosférica (hPa) - 18:20h às 00:00h',
    fontsize=12,
    fontweight='bold'
)

plt.xlabel('Horário da Leitura')
plt.ylabel('Pressão (hPa)')

plt.grid(True, linestyle='--')

plt.tight_layout()
plt.show()
