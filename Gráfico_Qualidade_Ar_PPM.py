import matplotlib.pyplot as plt
import datetime

# ==========================================
# QUALIDADE DO AR (PPM)
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

qualidade_ar = [
    420, 430, 440, 450, 460,
    470, 480, 490, 500, 510,
    520, 530, 540, 550, 560
]

plt.figure(figsize=(9,4.5))

plt.plot(
    tempos_str,
    qualidade_ar,
    color='purple',
    marker='v',
    linewidth=2
)

plt.title(
    'Qualidade do Ar (PPM) - 18:20h às 00:00h',
    fontsize=12,
    fontweight='bold'
)

plt.xlabel('Horário da Leitura')
plt.ylabel('PPM')

plt.grid(True, linestyle='--')

plt.tight_layout()
plt.show()
