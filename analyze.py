import matplotlib.pyplot as plt
from collections import defaultdict

def parse_file(filename):
    data = {}
    with open(filename, 'r', encoding='latin-1', errors='ignore') as f:
        for line_num, line in enumerate(f, 1):
            try:
                parts = line.strip().split()
                if len(parts) < 6:
                    continue
                key = parts[0]
                value = float(parts[5])
                data[key] = value
            except (ValueError, IndexError, UnicodeDecodeError):
                continue
    return data


iga_data = parse_file('BRKGA_RESUMO_IGA.txt')
ktns_data = parse_file('BRKGA_RESUMO_KTNS.txt')
iga_color = '#7CBD7C'
ktns_color = 'black'

combined = {}
for key in set(iga_data) | set(ktns_data):
    iga_val = iga_data.get(key, None)
    ktns_val = ktns_data.get(key, None)
    if iga_val is not None and ktns_val is not None:
        combined[key] = (iga_val, ktns_val)


sorted_items = sorted(combined.items(), key=lambda item: item[1][1])  # сортируем по KTNS

iga_values = [v[0] for k, v in sorted_items]
ktns_values = [v[1] for k, v in sorted_items]
indexes = range(len(sorted_items))

plt.figure(figsize=(15, 6))
plt.scatter(indexes, iga_values, color=iga_color, label='IGA', marker='o', s=5)
plt.scatter(indexes, ktns_values, color=ktns_color, label='KTNS', marker='o', s=5)
for i, (iga, ktns) in enumerate(zip(iga_values, ktns_values)):
    color = 'red' if iga > ktns else 'green'
    alpha = 1 if iga > ktns else 0.6
    linewidth = 1 if iga > ktns else 0.3
    plt.plot([i, i], [iga, ktns], color=color, linewidth=linewidth, alpha=alpha)
plt.xlabel('Тестовые случаи (индексы)')
plt.ylabel('Время выполнения (секунды)')
plt.title('Общее сравнение времени выполнения IGA и KTNS')
plt.xticks([])
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()


grouped = defaultdict(list)
for key, (iga_val, ktns_val) in combined.items():
    try:
        group = int(key.strip().split("_")[-1])
        grouped[group].append((iga_val, ktns_val))
    except ValueError:
        continue


groups = sorted(grouped.keys())
avg_iga, avg_ktns = [], []
max_iga, max_ktns = [], []
min_iga, min_ktns = [], []

for group in groups:
    iga_vals = [v[0] for v in grouped[group]]
    ktns_vals = [v[1] for v in grouped[group]]
    
    avg_iga.append(sum(iga_vals) / len(iga_vals))
    avg_ktns.append(sum(ktns_vals) / len(ktns_vals))
    
    max_iga.append(max(iga_vals))
    max_ktns.append(max(ktns_vals))
    
    min_iga.append(min(iga_vals))
    min_ktns.append(min(ktns_vals))

x = range(len(groups))

bar_width = 0.05
plt.figure(figsize=(12, 6))
plt.bar(x, avg_iga, bar_width, label='IGA - Среднее', color = iga_color)
plt.bar([i + bar_width for i in x], avg_ktns, bar_width, label='KTNS - Среднее', color = ktns_color)
plt.xticks([i + bar_width / 2 for i in x], groups)
plt.xlabel('Группа тестов')
plt.ylabel('Среднее время выполнения (секунды)')
plt.title('Среднее время выполнения по группам')
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()


plt.figure(figsize=(12, 6))
plt.bar(x, max_iga, bar_width, label='IGA - Макс', color = iga_color)
plt.bar([i + bar_width for i in x], max_ktns, bar_width, label='KTNS - Макс', color = ktns_color)
plt.xticks([i + bar_width / 2 for i in x], groups)
plt.xlabel('Группа тестов')
plt.ylabel('Максимальное время выполнения (секунды)')
plt.title('Максимальное время выполнения по группам')
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()


plt.figure(figsize=(12, 6))
plt.bar(x, [max_ - min_ for max_, min_ in zip(max_iga, min_iga)],
        bar_width, bottom=min_iga, label='IGA - Диапазон', color = iga_color)
plt.bar([i + bar_width for i in x], [max_ - min_ for max_, min_ in zip(max_ktns, min_ktns)],
        bar_width, bottom=min_ktns, label='KTNS - Диапазон', color = ktns_color)
plt.xticks([i + bar_width / 2 for i in x], groups)
plt.xlabel('Группа тестов')
plt.ylabel('Диапазон времени выполнения (секунды)')
plt.title('Диапазон выполнения по группам (от min до max)')
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
