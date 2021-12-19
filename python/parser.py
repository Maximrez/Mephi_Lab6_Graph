import requests
from bs4 import BeautifulSoup


def parse_schedule(room_url, group_names):
    response = requests.get(room_url)
    soup = BeautifulSoup(response.text, 'xml')
    quotes = soup.find_all('a')
    names = list(str(quote.text).rstrip() for quote in quotes)

    groups = list()
    index = 0
    while index < len(names):
        while index < len(names) and names[index] not in group_names:
            index += 1

        together = list()
        while index < len(names) and names[index] in group_names:
            together.append(names[index])
            index += 1
        if len(together) > 1 and together not in groups:
            groups.append(together)
    return groups


domen = 'https://home.mephi.ru'

all_quotes = []
for i in range(4):
    url = domen + '/study_groups?level=' + str(i) + '&organization_id=1&term_id=13'
    response = requests.get(url)
    soup = BeautifulSoup(response.text, 'lxml')
    quotes = soup.find_all('a', class_='list-group-item text-center text-nowrap')
    all_quotes += quotes

n = len(all_quotes)
groups_dict = {}
with open("../group_list.txt", "w", encoding="utf-8") as f:
    f.write(str(n))
    i = 0
    for quote in all_quotes:
        f.write("\n")
        group_name = str(quote.text).rstrip()
        f.write(group_name)
        groups_dict[group_name] = i
        i += 1

matrix = [[0] * n for i in range(n)]

url = domen + '/rooms?term_id=13'
response = requests.get(url)
soup = BeautifulSoup(response.text, 'lxml')
quotes = soup.find_all('a', class_='btn btn-primary btn-outline')

ignore = ["каф.15/2", "каф. 15/3", "Спорт. корпус, зал гимнастики", "Спорт. корпус, зал самбо",
          "Спорт. корпус, игровой зал", "Спорт. корпус, метод. каб.", "Спорт. корпус, плоскостные сооружения МИФИ",
          "Открытые спорт площадки МИФИ", "Открытые спорт площадки МИФИ, парк Коломенское", "каф.12", "каф.13",
          "Бассейн (аренда)", "Братеевские пруды", "ИБРАЭ РАН", "каф.40", "каф.5", "Скалодром",
          "Спортивный комплекс МИСиС (ул. Профсоюзная 83б)", "каф.20", "Спорт. корпус, зал гимнастики",
          "Спорт. корпус, зал самбо", "Спорт. корпус, игровой зал", "Спорт. корпус, метод. каб.",
          "Спорт. корпус, плоскостные сооружения МИФИ", "Игровой зал (Каширское шоссе, 64)", "каф.6", "каф.14",
          "В-210а"]

for quote in quotes:
    room_name = str(quote.text).rstrip()
    if room_name not in ignore:
        room_url = domen + str(quote).split('"')[3]
        # print(room_name, room_url)

        for groups_list in parse_schedule(room_url, list(groups_dict.keys())):
            for i in range(len(groups_list) - 1):
                for j in range(i + 1, len(groups_list)):
                    if groups_list[i] != groups_list[j]:
                        matrix[groups_dict[groups_list[i]]][groups_dict[groups_list[j]]] = 1
                        matrix[groups_dict[groups_list[j]]][groups_dict[groups_list[i]]] = 1

with open("../adjacency_matrix.txt", "w", encoding="utf-8") as f:
    f.write(str(n))
    for line in matrix:
        f.write("\n")
        f.write((" ").join(list(str(x) for x in line)))
#
# room_url = "https://home.mephi.ru/rooms/3780046"
# parse_schedule(room_url, list(groups_dict.keys()))
# for groups_list in parse_schedule(room_url):
#     for i in range(len(groups_list) - 1):
#         for j in range(i + 1, len(groups_list)):
#             matrix[groups_dict[groups_list[i]]][groups_dict[groups_list[j]]] = 1
#             matrix[groups_dict[groups_list[j]]][groups_dict[groups_list[i]]] = 1
