import matplotlib.pyplot as plt

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
            except (ValueError, IndexError, UnicodeDecodeError) as e:
                continue
    return data

# Парсим оба файла
iga_data = parse_file('BRKGA_RESUMO_IGA.txt')
ktns_data = parse_file('BRKGA_RESUMO_KTNS.txt')

combined = {}
for key in set(iga_data) | set(ktns_data):
    iga_val = iga_data.get(key, None)
    ktns_val = ktns_data.get(key, None)
    if iga_val is not None and ktns_val is not None:
        combined[key] = (iga_val, ktns_val)


labels = range(len(combined))
iga_values = [v[0] for v in combined.values()]
ktns_values = [v[1] for v in combined.values()]


plt.figure(figsize=(15, 6))
bar_width = 0.35
indexes = range(len(combined))


plt.bar(indexes, iga_values, bar_width, label='IGA', alpha=0.7)
plt.bar([i + bar_width for i in indexes], ktns_values, bar_width, label='KTNS', alpha=0.7)

plt.xlabel('Тестовые случаи (индексы)')
plt.ylabel('Время работы')
plt.title('Сравнение времени выполнения алгоритмов')
plt.xticks([]) 
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()

plt.show()
