import matplotlib.pyplot as plt
import datetime

# ==========================================
# UMIDADE RELATIVA
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

umidade = [
    60, 61, 62, 63, 64,
    65, 66, 67, 68, 69,
    70, 71, 72, 73, 74
]

plt.figure(figsize=(9,4.5))

plt.plot(
    tempos_str,
    umidade,
    color='blue',
    marker='s',
    linewidth=2
)

plt.title(
    'Variação de Umidade Relativa (%) - 18:20h às 00:00h',
    fontsize=12,
    fontweight='bold'
)

plt.xlabel('Horário da Leitura')
plt.ylabel('Umidade (%)')

plt.grid(True, linestyle='--')

plt.tight_layout()
plt.show()
