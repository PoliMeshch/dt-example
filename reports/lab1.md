# Лабораторная работа 1

## Ход работы

### Этап 1. Установка и настройка программы `git`

#### 1.1. Установка `git`
`git` был установлен с официального сайта [git-scm.com](https://git-scm.com).

#### 1.2. Проверка установки

```bash
git --version
```

Вывод:

```
git version 2.53.0.windows.1
```

Убедилась, что `git` установлен корректно и доступен в командной строке.

#### 1.3. Настройка пользователя

```bash
git config --global user.name "Полина Мещерякова"
git config --global user.email "polinamesh00@mail.ru"
```

Проверка настроек:

```bash
git config --global --list
```

Вывод:

```
gui.recentrepo=C:/Users/darel/dt-example
user.email=polinamesh00@mail.ru
user.name=Полина Мещерякова
```

Настроила глобальные параметры пользователя.

#### 1.4. Изучение справки

```bash
git --help
```

Ознакомилась со списком основных команд Git. Справка показывает разделы:
- Создание репозитория (`clone`, `init`)
- Работа с текущими изменениями (`add`, `mv`, `restore`, `rm`)
- Просмотр истории и состояния (`status`, `log`, `diff`)
- Работа с ветками и коммитами (`branch`, `commit`, `merge`, `rebase`)
- Совместная работа (`fetch`, `pull`, `push`)

Для получения подробной информации по конкретной команде используется `git help <команда>`.


### Этап 2. Начало работы с новым проектом

#### 2.1. Создание репозитория
Переход в папку проекта и инициализация репозитория:

```bash
cd dt-example
git init
```

Вывод:

```
Initialized empty Git repository in C:/Users/darel/dt-example/.git/
```

Создан новый репозиторий в папке `dt-example`.
Появилась скрытая папка `.git`, в которой Git будет хранить историю изменений.

#### 2.2. Создание структуры файлов
Создание в этом репозитории файла README.md, директории reports и файла reports/lab1.md.

```bash
touch README.md
mkdir reports
touch reports/lab1.md
```

Проверка структуры:

```bash
ls -la
```

Вывод:

```
total 24
drwxr-xr-x 1 darel 197614 0 Feb 22 18:16 ./
drwxr-xr-x 1 darel 197614 0 Feb 22 21:20 ../
drwxr-xr-x 1 darel 197614 0 Feb 22 21:54 .git/
-rw-r--r-- 1 darel 197614 0 Feb  6 15:15 README.md
drwxr-xr-x 1 darel 197614 0 Feb 22 21:51 reports/
```

#### 2.3. Изучение Markdown
Markdown — язык разметки, который позволяет оформлять текст, используя простые символы.
Файлы с расширением `.md` автоматически красиво отображаются на GitHub.

**Источники:**
- [Официальная шпаргалка по Markdown](https://www.markdownguide.org/cheat-sheet/)
- [Руководство по Markdown от GitHub](https://docs.github.com/ru/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)

**Основные синтаксические элементы:**

```markdown
# Заголовок первого уровня
## Заголовок второго уровня
### Заголовок третьего уровня

**жирный текст**
*курсив*
~~зачеркнутый~~

`git status` — выделение кода или команд

[текст ссылки](https://example.com)

![альтернативный текст](путь/к/изображению.png)
```

#### 2.4. Наполнение README.md
Открыт файл `README.md` в текстовом редакторе и добавлена следующая информация:

```markdown
# Лабораторные работы по Современным технологиям разработки ПО

Выполнил студент: Мещерякова Полина Алексеевна, группа 5130201/50302
```

#### 2.5. Первый коммит
Добавление файлов в индекс:

```bash
git add README.md
git add reports/lab1.md
```

Проверка состояния после добавления:

```bash
git status
```

Вывод:

```
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   README.md
        new file:   reports/lab1.md
```

Коммит:

```bash
git commit -m "Начальная структура репозитория: README и шаблон отчета"
```

Вывод:

```
[master (root-commit) 805ed14] Начальная структура репозитория: README и шаблон отчета
 2 files changed, 3 insertions(+)
 create mode 100644 README.md
 create mode 100644 reports/lab1.md
```

**Результат:**
- Создан Git-репозиторий
- Создана структура: `README.md`, папка `reports/`, файл `reports/lab1.md`
- Изучен синтаксис Markdown для оформления отчета
- В `README.md` добавлена информация о дисциплине и студенте
- Выполнен первый коммит


### Этап 3. Отслеживание состояния кода

#### 3.1. Изучение команд git status и git diff

Команда:

```bash
git status
```

Вывод:

```
On branch master
nothing to commit, working tree clean
```

Команда:

```bash
git diff
```

Пустой вывод.

**Что делают эти команды:**
- `git status` — показывает состояние файлов относительно последнего коммита. Сейчас все файлы сохранены, изменений нет.
- `git diff` — показывает построчные изменения в файлах, которые еще не добавлены в индекс. Сейчас изменений нет, поэтому вывод пустой.

#### 3.2. Перенос заметок в отчет
В файл `reports/lab1.md` добавлено описание этапов 1 и 2.

#### 3.3. Проверка состояния после заполнения отчета
Команда:

```bash
git status
```

Вывод:

```
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   reports/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

Команда:

```bash
git diff
```

Вывод:

```
diff --git a/reports/lab1.md b/reports/lab1.md
index e69de29..d6c0ada 100644
--- a/reports/lab1.md
+++ b/reports/lab1.md
@@ -0,0 +1,218 @@
+# <CB><E0><E1><EE><F0><E0><F2><EE><F0><ED><E0><FF> <F0><E0><E1><EE><F2><E0> 1
+
+## <D5><EE><E4> <F0><E0><E1><EE><F2><FB>
+
+### <DD><F2><E0><EF> 1. <D3><F1><F2><E0><ED><EE><E2><EA><E0> <E8> <ED><E0><F1>
<F2><F0><EE><E9><EA><E0> <EF><F0><EE><E3><F0><E0><EC><EC><FB> `git`
+
+#### 1.1. <D3><F1><F2><E0><ED><EE><E2><EA><E0> `git`
+`git` <E1><FB><EB> <F3><F1><F2><E0><ED><EE><E2><EB><E5><ED> <F1> <EE><F4><E8>
<F6><E8><E0><EB><FC><ED><EE><E3><EE> <F1><E0><E9><F2><E0> [git-scm.com](https://git-scm.com).
+
+#### 1.2. <CF><F0><EE><E2><E5><F0><EA><E0> <F3><F1><F2><E0><ED><EE><E2><EA><E8>
+
+```bash
+git --version
+```
+
```

**Объяснение вывода:**
- `git status` показывает, что файл `reports/lab1.md` изменен, но изменения еще не добавлены в индекс
- `git diff` показывает конкретные добавленные строки (они помечены знаком `+`). В выводе видны нечитаемые 
символы — это особенность отображения кириллицы в Git Bash на Windows. Файл сохранен в кодировке UTF-8, и 
при просмотре в терминале русские буквы отображаются как коды, но сам файл содержит корректный текст. 