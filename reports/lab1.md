# Лабораторная работа 1

## Ход работы

### Этап 1. Установка и настройка программы `git`

#### 1.1. Установка `git`
`git` был установлен с официального сайта [git-scm.com](https://git-scm.com).

#### 1.2. Проверка установки

```bash
git --version
```

**Вывод:**

```
git version 2.53.0.windows.1
```

Убедилась, что `git` установлен корректно и доступен в командной строке.

#### 1.3. Настройка пользователя

```bash
git config --global user.name "Полина Мещерякова"
git config --global user.email "polinamesh00@mail.ru"
```

**Проверка настроек:**

```bash
git config --global --list
```

**Вывод:**

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
**Переход в папку проекта и инициализация репозитория:**

```bash
cd dt-example
git init
```

**Вывод:**

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

**Проверка структуры:**

```bash
ls -la
```

**Вывод:**

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
**Добавление файлов в индекс:**

```bash
git add README.md
git add reports/lab1.md
```

**Проверка состояния после добавления:**

```bash
git status
```

**Вывод:**

```
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   README.md
        new file:   reports/lab1.md
```

**Коммит:**

```bash
git commit -m "Начальная структура репозитория: README и шаблон отчета"
```

**Вывод:**

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
**Команда:**

```bash
git status
```

**Вывод:**

```
On branch master
nothing to commit, working tree clean
```

**Команда:**

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
**Команда:**

```bash
git status
```

**Вывод:**

```
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   reports/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

**Команда:**

```bash
git diff
```

**Вывод:**

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
- `git diff` показывает конкретные добавленные строки (они помечены знаком `+`). Нечитаемые символы в угловых 
скобках — это результат несоответствия кодировок: файл был сохранён в однобайтовой кодировке 
Windows, а Git Bash ожидает UTF-8.

*Примечание*: Позже в ходе работы кодировка файла была исправлена на UTF-8, что позволило корректно отображать
кириллицу как в терминале, так и в редакторах кода.
Как должны были выглядеть добавленные строки (после исправления кодировки):

```
diff --git a/reports/lab1.md b/reports/lab1.md
index e69de29..d6c0ada 100644
--- a/reports/lab1.md
+++ b/reports/lab1.md
@@ -0,0 +1,218 @@
+# Лабораторная работа 1
+
+## Ход работы
+
+### Этап 1. Установка и настройка программы `git`
+
+#### 1.1. Установка `git`
+`git` был установлен с официального сайта [git-scm.com](https://git-scm.com).
+
+#### 1.2. Проверка установки
+
+
bash
+git --version
```

#### 3.4. Добавление изменений в индекс

**Команда:**

```bash
git add reports/lab1.md
git status
```

**Вывод:**

```
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   reports/lab1.md
```

**Объяснение:** Файл добавлен в индекс (staging area) — готов к коммиту, но коммит еще не сделан.

#### 3.5. Изменение README.md и просмотр изменений
В файл README.md добавлена строка: "123456789".
Кроме того, строка с именем студента была повторно добавлена в файл 
(удалена и вставлена заново), что также отразилось в выводе git diff.

**Команда:**

```bash
git diff README.md
```

**Вывод:**

```
diff --git a/README.md b/README.md
index 29315bc..738da36 100644
--- a/README.md
+++ b/README.md
@@ -1,3 +1,4 @@
 # <CB><E0><E1><EE><F0><E0><F2><EE><F0><ED><FB><E5> <F0><E0><E1><EE><F2><FB>
<EF><EE> <D1><EE><E2><F0><E5><EC><E5><ED><ED><FB><EC> <F2><E5><F5><ED><EE><EB>
<EE><E3><E8><FF><EC> <F0><E0><E7><F0><E0><E1><EE><F2><EA><E8> <CF><CE>

+<C2><FB><EF><EE><EB><ED><E8><EB> <F1><F2><F3><E4><E5><ED><F2>: <CC><E5><F9><E5><F0><FF><EA><EE><E2><E0> <CF><EE><EB><E8><ED><E0> <C0><EB><E5><EA><F1><E5><E5>
<E2><ED><E0>, <E3><F0><F3><EF><EF><E0> 5130201/50302.
+123456789
\ No newline at end of file
```

**Объяснение:** git diff с указанием имени файла показывает изменения только в этом файле.
В выводе видны две добавленные строки (помечены знаком +):

1. Строка с именем студента и группы
2. Строка 123456789 для демонстрации

*Примечание*: После исправления кодировки файла (см. п. 3.6) вывод git diff для этого же изменения выглядит следующим образом:

```
diff --git a/README.md b/README.md
index 29315bc..738da36 100644
--- a/README.md
+++ b/README.md
@@ -1,3 +1,4 @@
 # Лабораторные работы по Современным технологиям разработки ПО

+Выполнил студент: Мещерякова Полина Алексеевна, группа 5130201/50302.
+123456789
\ No newline at end of file
```

#### 3.6. Коммит только отчета

**Команда:**

```bash
git commit -m "Добавила описание этапов 1-3 в отчет"
```

**Вывод:**

```
[master f4725b5] Добавила описание этапов 1-3 в отчет
 1 file changed, 281 insertions(+)
 ```


### Этап 4. Откат изменений

#### 4.1. Проверка незакоммиченных изменений
**Проверка состояния:**

```bash
git status
```

**Вывод:**

```
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

**Объяснение:** Закоммичен только отчет. README.md остался измененным, но не закоммиченным.
Это показывает, что Git позволяет коммитить файлы выборочно.

#### 4.2. Откат изменений в README.md

```bash
git restore README.md
git status
```

**Вывод:**

```
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   reports/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

**Объяснение:** Изменения в README.md отменены. Файл вернулся к состоянию последнего коммита.

#### 4.3. Сохранение копии и удаление файла отчета 

**Создание резервной копии:**

```bash
cp reports/lab1.md reports/lab1.md.bak
```

**Удаление:**

```bash
rm reports/lab1.md
```

#### 4.4. Проверка состояния после удаления

```bash
git status
```

**Вывод:**

```
On branch master
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    reports/lab1.md

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        reports/lab1.md.bak

no changes added to commit (use "git add" and/or "git commit -a")
```

**Объяснение:** Git показывает, что создана копия reports/lab1.md.bak и
файл reports/lab1.md удалён из рабочей директории.

#### 4.5. Восстановление удаленного файла

```bash
git restore reports/lab1.md
git status
```

**Вывод:**

 ```
 On branch master
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        reports/lab1.md.bak

nothing added to commit but untracked files present (use "git add" to track)
```


### Этап 5. Ветвление версий

#### 5.1. Вывод текущей ветки

```bash
git branch
```

**Вывод:** 

```
* master
```

Звездочка * показывает текущую ветку. Сейчас мы находимся в ветке master.

#### 5.2. Создание новой ветки и переключение на неё

```bash
git checkout -b lab1-1
```

**Вывод:** 

```
Switched to a new branch 'lab1-1'
```

##### 5.3. Внесение изменений в отчет и коммит
Добавление в reports/lab1.md описание этапов 3-5 в отчет

```bash
git add reports/lab1.md
git commit -m "Добавила описание этапов 3-5 в отчет (работа в ветке lab1-1)"
```
**Вывод:** 

```
[lab1-1 b3b26e0] Добавила описание этапов 3-5 в отчет (работа в ветке lab1-1)
 1 file changed, 218 insertions(+), 21 deletions(-)
```

#### 5.4. Проверка наличия изменений

```bash
cat reports/lab1.md
```

Вывод показывает содержимое файла с добавленными этапами.
Изменения сохранены в файле и закоммичены в ветке lab1-1.

#### 5.5. Переключение обратно на ветку master

```bash
git checkout master
```

**Вывод:** 

```
Switched to branch 'master'
```
**Проверка содержимого отчета:**

```bash
cat reports/lab1.md
```

Вывод показывает содержимое без этапов 3-5

**Объяснение:** в ветке master нет изменений, сделанных в ветке lab1-1. Ветки изолированы друг от друга.

#### 5.6. Изменение README.md и попытка переключения
Добавлена строка: "Проверка переключения между ветками".

**Проверка статуса:**

```bash
git status
```
**Вывод:** 

```
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

**Попытка переключиться на ветку lab1-1:**

```bash
git checkout lab1-1
```

**Вывод:** 

```
M       README.md
Switched to branch 'lab1-1'
```

**Объяснение результата**: Git разрешил переключение, потому что файл README.md в коммитах веток 
master и lab1-1 идентичен (не менялся в коммите b3b26e0). Незакоммиченные изменения были просто 
перенесены в другую ветку, о чём сообщает пометка M (modified). Если бы файл в ветках различался 
(например, в lab1-1 были сделаны другие коммиты с изменениями README.md), Git бы выдал ошибку, 
так как не смог бы разрешить конфликт между версиями файла.

### Этап 6. Слияние веток, конфликты
##### 6.1. Откат изменений в README.md
Сначала убеждаюсь, что я нахожусь в ветке lab1-1 (после предыдущего шага):

```bash
git branch
```

**Вывод:** 

```
  master
* lab1-1
```

**Откатываю изменения в README.md:**

```bash
git restore README.md
git status
```

**Вывод:** 

```
On branch lab1-1
nothing to commit, working tree clean
```

#### 6.2. Слияние ветки lab1-1 в основную (master)
**Переключаюсь на основную ветку:**

```bash
git checkout master
```

**Вывод:** 

```
Switched to branch 'master'
```

**Выполняю слияние:**

```bash
git merge lab1-1
```

**Вывод:** 

```
Updating f4725b5..b3b26e0
Fast-forward
 reports/lab1.md | 218 +++++++++++++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 217 insertions(+), 1 deletion(-)
```

**Объяснение:** Произошло fast-forward слияние, потому что ветка master не имела новых 
коммитов после расхождения с lab1-1. Git просто переместил указатель master на коммит 
из lab1-1. Теперь в master появились описания этапов 3-5 из отчета.

#### 6.3. Изменение заголовка в README.md и коммит
Изменяю заголовок в README.md на "# Лабораторные работы по Git".
В процессе редактирования сначала был ошибочно введён вариант без символа заголовка, 
который затем был удалён. Это отразилось в выводе git как 2 добавленные и 2 удалённые строки.

```bash
git add README.md
git commit -m "Изменила заголовок README.md в ветке master"
```

**Вывод:** 

```
[master 8a6e149] Изменила заголовок README.md в ветке master
 1 file changed, 2 insertions(+), 2 deletions(-)
 ```

 #### 6.4. Переключение на ветку lab1-1 и внесение изменений

```bash
git checkout lab1-1
```

**Вывод:** 

```
Switched to branch 'lab1-1'
```

**Вношу три изменения:**

1. Добавляю новые части в отчет — открываю reports/lab1.md и дописываю описание 5 этапа и часть 6 этапа.
2. Изменяю заголовок README.md: "# Работа с Git в лабораторных".
3. Добавляю строку в конец README.md: "Это строка добавлена в ветке lab1-1".

#### 6.5. Коммит изменений в ветке lab1-1 и попытка слияния lab1-1 с master

```bash
git add README.md reports/lab1.md
git commit -m "Изменила заголовок README и добавила части этапов 5-6 в отчет (ветка lab1-1)"
```

**Вывод:** 

```
[lab1-1 eaa5e16] Изменила заголовок README и добавила части этапов 5-6 в отчет (ветка lab1-1)
 2 files changed, 360 insertions(+), 128 deletions(-)
```
**Попытка слияния:**

```bash
git checkout master
git merge lab1-1
```

**Вывод:** 

```
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Automatic merge failed; fix conflicts and then commit the result.
```
**Объяснение:** Возник конфликт, потому что в обеих ветках был изменён один и тот же файл README.md. 
Git не может автоматически решить, какой вариант правильный. Слияние приостановлено до разрешения конфликта. 
Файл reports/lab1.md также был изменён в обеих ветках, но конфликта там не возникло, так как изменения были 
в разных частях файла.

#### 6.6. Просмотр содержимого README.md, разрешение конфликта

```bash
cat README.md
```
**Вывод:** 

```
<<<<<<< HEAD
# Лабораторные работы по Git

Выполнил студент: Мещерякова Полина Алексеевна, группа 5130201/50302.
=======
# Работа с Git в лабораторных

Выполнил студент: Мещерякова Полина Алексеевна, группа 5130201/50302.
Это строка добавлена в ветке lab1-1.
>>>>>>> lab1-1
```

**Разрешение конфликта:**
В VS Code выбрала опцию "Accept Current Change", оставив версию файла из текущей ветки `master`. 

**Коммит:**

```bash
git add README.md
git commit -m "Разрешила конфликт при слиянии lab1-1 в master"
```

**Вывод:** 

```
[master 43b1d22] Разрешила конфликт при слиянии lab1-1 в master
```

#### 6.7. Удаление ветки lab1-1

**Команда:**
```bash
git branch -d lab1-1
```

**Вывод:** 

```
Deleted branch lab1-1 (was eaa5e16).
```

**Объяснение:** Ветка lab1-1 удалена, так как её изменения уже влиты в master.
Флаг -d удаляет ветку только если она уже слита (безопасное удаление).


### Этап 7. Работа с удаленным репозиторием
#### 7.1-7.2. Настройка доступа к GitHub
SSH-ключ был настроен ранее. Подключение к GitHub проверено командой:

```bash
ssh -T git@github.com
```

**Вывод:**

```
Hi PoliMeshch! You've successfully authenticated, but GitHub does not provide shell access.
```

#### 7.3. Создание репозитория на GitHub
Создан приватный репозиторий `dt-example` без инициализационных файлов.

#### 7.4. Добавление удаленного репозитория

```bash
git remote add origin git@github.com:PoliMeshch/dt-example.git
git remote -v
```

**Вывод:**

```
origin  git@github.com:PoliMeshch/dt-example.git (fetch)
origin  git@github.com:PoliMeshch/dt-example.git (push)
```

#### 7.5. Отправка данных в удаленный репозиторий
```bash
git branch -M main
git push -u origin main
```

**Пояснения:** 
1. Команда 'git branch -M main' переименовывает текущую ветку в main.
Флаг -M принудительно переименовывает ветку, даже если ветка с таким именем уже существует.
В более старых версиях Git основная ветка называлась master, сейчас стандарт — main. Эта
команда приводит имя локальной ветки в соответствие с современными стандартами GitHub.
2. Команда 'git push -u origin main' отправляет локальные коммиты в удаленный репозиторий
на GitHub. Флаг -u устанавливает связь между локальной веткой main и удаленной origin/main,
чтобы в будущем можно было использовать просто git push. origin — это имя удаленного
репозитория по умолчанию.

**Вывод:**

```
Enumerating objects: 24, done.
Counting objects: 100% (24/24), done.
Delta compression using up to 4 threads
Compressing objects: 100% (19/19), done.
Writing objects: 100% (24/24), 12.10 KiB | 1.73 MiB/s, done.
Total 24 (delta 4), reused 0 (delta 0)
To github.com:PoliMeshch/dt-example.git
 * [new branch]      main -> main
Branch 'main' set up to track remote branch 'main' from 'origin'.
```

**Объяснение:** Git упаковал и отправил 30 объектов (коммиты и файлы) на GitHub,
где создалась новая ветка main. Теперь локальная ветка отслеживает удаленную, и
все изменения можно отправлять командой git push.


#### 7.6. Проверка отображения
На странице GitHub в репозитории dt-example отображаются все файлы: README.md и папка reports/ с файлом lab1.md.


### Этап 8. Синхронизация с удаленным репозиторием.
#### 8.1. Создание папки вне репозитория
Выхожу из текущей папки и создаю новую директорию для клона:

```bash
cd ..
mkdir dt-example-clone
```

#### 8.2. Клонирование репозитория

```bash
git clone git@github.com:PoliMeshch/dt-example.git dt-example-clone
```

**Вывод:**

```
Cloning into 'dt-example-clone'...
remote: Enumerating objects: 24, done.
remote: Counting objects: 100% (24/24), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 24 (delta 4), reused 24 (delta 4), pack-reused 0 (from 0)
Receiving objects: 100% (24/24), 12.10 KiB | 1.73 MiB/s, done.
Resolving deltas: 100% (4/4), done.
```

**Пояснение:**git clone создает полную копию удаленного репозитория в указанной папке.
GitHub отправил все файлы, коммиты и историю изменений.

#### 8.3. Проверка совпадения файлов
**Перехожу в клон и проверяю содержимое:**

```bash
cd dt-example-clone
ls -la
```

**Вывод:**

```
total 21
drwxr-xr-x 1 darel 197614   0 Mar  8 15:39 ./
drwxr-xr-x 1 darel 197614   0 Mar  8 15:34 ../
drwxr-xr-x 1 darel 197614   0 Mar  8 15:39 .git/
-rw-r--r-- 1 darel 197614 170 Mar  8 15:39 README.md
drwxr-xr-x 1 darel 197614   0 Mar  8 15:39 reports/
```

Полное совпадение с оригинальным репозиторием.

#### 8.4. Добавление в клоне последних протоколов в отчет
Открываю reports/lab1.md в клоне и добавляю описание этапов 6-7.

```bash
git add reports/lab1.md
git commit -m "Добавила описание этапов 6-7 в отчет"
```

**Вывод:**

```
[main bdd6b91] Добавила описание этапов 6-7 в отчет
 1 file changed, 185 insertions(+), 25 deletions(-)
```

#### 8.5. Отправка изменений в удаленный репозиторий

```bash
git push
```

**Вывод:**

```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (4/4), 3.00 KiB | 1.50 MiB/s, done.
Total 4 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To github.com:PoliMeshch/dt-example.git
   43b1d22..bdd6b91  main -> main
```

Новый коммит отправлен на GitHub.

#### 8.6. Возвращение в первый локальный репозиторий

```bash
cd ../dt-example
```

#### 8.7. Запрос обновлений

```bash
git fetch origin
```

**Вывод:**

```
remote: Enumerating objects: 7, done.
remote: Counting objects: 100% (7/7), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 4 (delta 1), reused 4 (delta 1), pack-reused 0 (from 0)
Unpacking objects: 100% (4/4), 2.98 KiB | 234.00 KiB/s, done.
From github.com:PoliMeshch/dt-example
   43b1d22..bdd6b91  main       -> origin/main
```

**Объяснение вывода команды:** git fetch скачал информацию о новых коммитах с GitHub, но
не применил их к рабочим файлам. Видно, что в удаленной ветке origin/main
появился новый коммит bdd6b91, которого нет в локальной ветке main.

#### 8.8. Синхронизация содержимого репозитория для основной ветки

```bash
git pull
```

**Вывод:**

```
Updating 43b1d22..bdd6b91
Fast-forward
 reports/lab1.md | 210 +++++++++++++++++++++++++++++++++++++++++++++++++-------
 1 file changed, 185 insertions(+), 25 deletions(-)
```

**Объяснение:** git pull скачал новые изменения с GitHub и сразу применил
их к текущей ветке. Произошло fast-forward слияние. Теперь локальный
репозиторий синхронизирован с удаленным.

### Этап 9. История изменений.

```bash
git log --oneline
```

**Вывод:**

```
bdd6b91 (HEAD -> main, origin/main, origin/HEAD) Добавила описание этапов 6-7 в отчет
43b1d22 Разрешила конфликт при слиянии lab1-1 в master
eaa5e16 Изменила заголовок README и добавила части этапов 5-6 в отчет (ветка lab1-1)
8a6e149 Изменила заголовок README.md в ветке master
b3b26e0 Добавила описание этапов 3-5 в отчет (работа в ветке lab1-1)
f4725b5 Добавила описание этапов 1-3 в отчет
805ed14 Начальная структура репозитория: README и шаблон отчета
```

**Добавлены коммиты:**

```bash
git commit -m "Завершила лабораторную работу №1"
git commit -m "Подготовила ветку submit-lab1 для проверки"
```
