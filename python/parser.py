import requests
from bs4 import BeautifulSoup

week_days = {'Понедельник': 0,
             'Вторник': 1,
             'Среда': 2,
             'Четверг': 3,
             'Пятница': 4,
             'Суббота': 5}


def add_edges(groups, wd, lt):
    edges = open("../edges.txt", "a", encoding="utf-8")

    for i in range(len(groups) - 1):
        for j in range(i + 1, len(groups)):
            if groups[i][1:3] == groups[j][1:3]:
                edges.write(groups[i] + " " + groups[j] + " " + str(wd) + " " + str(lt) + "\n")

    edges.close()


def parse_schedule(room_url, group_names):
    response = requests.get(room_url)
    soup = BeautifulSoup(response.text, 'lxml')
    quotes = list(map(lambda x: str(x.text).strip(), soup.find_all(["h3", "div", "a"], class_=["text-nowrap", "lesson-wday", "lesson-time"])))

    groups = list()
    wd = -1
    lt = ""

    for quote in quotes:
        if quote in week_days.keys():
            add_edges(groups, wd, lt)
            groups = list()
            wd = week_days[quote]
            lt = ""
        elif ":" in quote:
            add_edges(groups, wd, lt)
            groups = list()
            lt = str(quote[:5])
        elif quote in group_names and quote not in groups:
            groups.append(quote)
        else:
            add_edges(groups, wd, lt)
            groups = list()


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
          "Спорт. корпус, плоскостные сооружения МИФИ", "Игровой зал (Каширское шоссе, 64)", "каф.6", "каф.14"]

group_names = list(groups_dict.keys())

edges = open("../edges.txt", "w", encoding="utf-8")
edges.close()

for quote in quotes:
    room_name = str(quote.text).rstrip()
    if room_name not in ignore:
        room_url = domen + str(quote).split('"')[3]
        parse_schedule(room_url, group_names)

with open("../edges.txt", "a", encoding="utf-8") as f:
    f.write(".")