# Лабораторная работа 2

## Подготовка к работе

Создание нового файла `lab2.md` в папке для отчётов `reports`.

### Ход работы

### Этап 1. Подготовка репозитория.

#### 1.1. Создание структуры для кода

**Создание папки `labs` и вложенной папки `lab2`, переход в `lab2`:**

```bash
mkdir -p labs/lab2
cd labs/lab2
```

Добавила в папку `lab2` код программы второй лабораторной работы по Структурам данных: `lab2.cpp`.

#### 1.2. Изучение `.gitignore`

**Что такое `.gitignore`**

Файл `.gitignore` используется в git для указания файлов и папок, которые не должны попадать в репозиторий.
Это текстовый файл, в котором перечисляются шаблоны имен, и git автоматически игнорирует все объекты,
соответствующие этим шаблонам.

**Зачем нужен `.gitignore`**

В процессе разработки в папке проекта появляется множество файлов, которые не являются исходным кодом
и не должны храниться в репозитории. К таким файлам относятся объектные файлы (`.o`, `.obj`), исполняемые
файлы (`.exe`, `.out`), временные файлы (`.tmp`, `.log`), папки сборки (`build`, `dist`), а также файлы настроек
среды разработки (`.vscode`, `.idea`). Добавление этих файлов в репозиторий приводит к его захламлению и может
вызвать конфликты при работе нескольких разработчиков.

**Как работает `.gitignore`**

Правила в `.gitignore` записываются построчно. Можно указывать конкретные имена файлов, расширения с
звездочкой (`*.log`), целые папки (`build/`). Также поддерживаются комментарии (строки, начинающиеся с `#`).
git проверяет каждый файл перед добавлением в индекс и пропускает те, которые соответствуют шаблонам из `.gitignore`.

**Источники:**
1. [Документация Git](https://git-scm.com/docs/gitignore)
2. [Статья на Habr](https://habr.com/ru/articles/542732/)

#### 1.3. Создание `.gitignore`

В корне проекта создала файл `.gitignore`. В него добавила правила для игнорирования:

- Папок сборки (`build/`, `out/`, `bin/`, `obj/`)
- Объектных и исполняемых файлов (`*.o`, `*.obj`, `*.exe`, `*.out`)
- Временных файлов (`*.tmp`, `*.log`, `*.cache`)
- Файлов настроек сред разработки (`.vscode/`, `.idea/`)

#### 1.4. Проверка работы `.gitignore` и коммит

Для проверки работы `.gitignore` создала папку `build` внутри `labs/lab2` и добавила в
нее тестовый файл:

```bash
mkdir -p labs/lab2/build
touch labs/lab2/build/test.md
```

**Проверка статуса:**

```bash
git status
```
**Вывод:**

```
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore
        labs/
        reports/lab2.md

nothing added to commit but untracked files present (use "git add" to track)
```

Папка `build` и тестовый файл не отображаются в статусе, так как они попадают под правила `.gitignore`.
Значит, `.gitignore` работает корректно.

**Добавление файлов в индекс:**

```bash
git add .gitignore labs/
```
**Вывод:**

```
warning: in the working copy of 'labs/lab2/lab2.cpp', LF will be replaced by CRLF the next time Git touches it
```

*Примечание:* При добавлении файлов появилось предупреждение о замене символов перевода строки (LF на CRLF).
Это стандартное поведение git на Windows, связанное с разными форматами окончания строк в разных операционных системах.

**Проверка статуса после добавления:**

```bash
git status
```

**Вывод:**

```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   .gitignore
        new file:   labs/lab2/lab2.cpp

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        reports/lab2.md
```

```bash
git add reports/lab2.md
git status
git commit -m "Добавила структуру для лабораторных работ, .gitignore и шаблон отчета"
git push origin main
```

**Выводы:**

```
[main 3275b70] Добавила структуру для лабораторных работ, .gitignore и шаблон отчета
 3 files changed, 533 insertions(+)
 create mode 100644 .gitignore
 create mode 100644 labs/lab2/lab2.cpp
 create mode 100644 reports/lab2.md
```
```
Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 4 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (8/8), 8.45 KiB | 961.00 KiB/s, done.
Total 8 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To github.com:PoliMeshch/dt-example.git
   a02fb8f..3275b70  main -> main
```


### Этап 2. Защита веток.

#### 2.1. Изучение защиты веток в GitHub

**Что такое защита веток**

Защита веток (branch protection) — это набор правил для веток в репозитории GitHub, которые предотвращают
случайные или неавторизованные изменения. Защита настраивается для конкретных веток (обычно для `main`).

**Какие правила можно установить**

Можно запретить прямой пуш в ветку, требуя создания Pull Request для любых изменений. Можно требовать 
обязательное ревью от одного или нескольких разработчиков перед слиянием. Можно настаивать на прохождении 
автоматических проверок (CI/CD). Также можно запретить удаление ветки или требовать, чтобы ветка была актуальна 
относительно основной перед слиянием.

**Зачем это нужно**

Защита веток обеспечивает контроль качества кода, позволяет проводить ревью, предотвращает случайное внесение 
ошибок в основную ветку и упрощает командную работу.

**Источник:** [GitHub Docs](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/
managing-protected-branches/about-protected-branches)

#### 2.2. Настройка защиты ветки main на GitHub

Для защиты ветки `main` от прямых изменений необходимо настроить правило, требующее создания Pull Request для любых изменений.

**Порядок действий на GitHub:**

1. Перейти в настройки репозитория
2. Выбрать **Branches** в левом меню
3. Нажать **Add classic branch protection rule**
4. В поле **Branch name pattern** ввести "main"
5. Установить защиту **Require a pull request before merging**
6. Установить количество требуемых одобрений: 1
7. Включить опцию **Do not allow bypassing the above settings**
8. Нажать **Create**

**Замечания по настройке:**

- В бесплатной версии GitHub правила защиты веток применяются только к публичным репозиториям. Мой репозиторий был приватным, 
поэтому для демонстрации работы защиты я временно изменила видимость репозитория на публичную.
- Опция "Do not allow bypassing the above settings" критически важна: без неё администраторы могут обходить защиту, и пуш в `main`
будет успешным (хотя GitHub покажет предупреждение "Bypassed rule violations"). После включения этой опции защита начинает работать 
в полную силу для всех пользователей, включая владельца репозитория.

#### 2.3. Проверка защиты

```bash
echo "# Тест" >> README.md
git add README.md
git commit -m "Тестовый коммит"
git push origin main
```

**Вывод:**

```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 347 bytes | 347.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
remote: error: GH006: Protected branch update failed for refs/heads/main.
remote:
remote: - Changes must be made through a pull request.
To github.com:PoliMeshch/dt-example.git
 ! [remote rejected] main -> main (protected branch hook declined)
error: failed to push some refs to 'github.com:PoliMeshch/dt-example.git'
```

```bash
git reset --hard HEAD~1
```

*Примечание:* Тестовый коммит был успешно заблокирован защитой веток, что подтверждает корректность настроек. 
Локальный коммит удалён командой `git reset`.

#### 2.4. Создание ветки pr-test

После настройки защиты основной ветки создала новую ветку `pr-test` и проверила возможность пуша в удаленный репозиторий.

```bash
git checkout -b pr-test
git push origin pr-test
```

**Вывод:**

```
Total 0 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
remote:
remote: Create a pull request for 'pr-test' on GitHub by visiting:
remote:      https://github.com/PoliMeshch/dt-example/pull/new/pr-test
remote:
To github.com:PoliMeshch/dt-example.git
 * [new branch]      pr-test -> pr-test
```

**Результат:** Ветка `pr-test` успешно отправлена в удаленный репозиторий. В отличие от `main`, в эту ветку пушить можно 
без ограничений.

#### 2.5. Сохранение результатов этапа в отчете

После завершения настройки и проверки защиты веток зафиксировала изменения в отчете:

```bash
git add reports/lab2.md
git commit -m "Добавила описание этапа 2 в отчет"
git push origin main
```


### Этап 3. Запросы на слияние

#### 3.1. Изменения в ветке `pr-test`

В ветке `pr-test` внесла изменения для демонстрации процесса создания Pull Request.

```bash
echo "# Тестовый PR" >> README.md
git add README.md
git commit -m "Добавила комментарий в README из ветки pr-test"
git push origin pr-test
```

**Вывод:**

```
Enumerating objects: 11, done.
Counting objects: 100% (11/11), done.
Delta compression using up to 4 threads
Compressing objects: 100% (7/7), done.
Writing objects: 100% (7/7), 4.80 KiB | 1.60 MiB/s, done.
Total 7 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To github.com:PoliMeshch/dt-example.git
   3275b70..6cdd9fd  pr-test -> pr-test
```

#### 3.2. Создание Pull Request на GitHub

Через веб-интерфейс GitHub создала Pull Request из ветки `pr-test` в `main`:

1. Перешла в репозиторий на GitHub
2. Нажала вкладку **Pull requests**
3. Нажала **New pull request**
4. Выбрала:
  - base: main
  - compare: pr-test
5. Нажала **Create pull request**
6. Заполнила:
  - Title: "Тестовый PR для проверки Git Flow"
  - Description: "Демонстрация создания и принятия Pull Request"
7. Нажала **Create pull request**

#### 3.3. Принятие PR и слияние

Для выполнения слияния и возможности коммитить изменения в отчет в процессе работы я временно отключила 
защиту ветки `main` в настройках репозитория. После этого:
- Выполнила слияние PR через веб-интерфейс
- Смогла коммитить и пушить изменения в отчет напрямую

После завершения этапа 3 защита будет восстановлена для следующего этапа работы.

#### 3.4. Обновление локального репозитория

После слияния на GitHub обновила локальную ветку `main`:

```bash
git checkout main
git pull origin main
```

**Результат:** Локальная ветка `main` синхронизирована с удаленным репозиторием, изменения из `pr-test` успешно влиты.

#### 3.5. Сохранение результатов этапа в отчете

Зафиксировала изменения в отчете:

```bash
git add reports/lab2.md
git commit -m "Добавила описание этапа 3 в отчет"
git push origin main
```

### Этап 4. Code Review

#### 4.1. Создание новой ветки для лабораторной работы

Создала от `main` новую ветку `prog-lab2` (названа в соответствии с номером лабораторной работы) и переключилась на нее:

```bash
git checkout -b prog-lab2
```

#### 4.2. Работа над 2 лабораторной работой по Структурам данных

В процессе подготовки лабораторной работы по Структурам данных были сделаны следующие коммиты:

```bash
git add src/
git commit -m "Добавила исходный код для лабораторной работы №2"

git add .gitignore
git commit -m "Добавила .gitignore"

git add tests/
git commit -m "Добавила тесты"

git add Makefile
git commit -m "Добавила Makefile для сборки проекта"

git add src/lab2.cpp
git commit -m "Добавила комментарий для демонстрации работы над кодом"

# Удалила .gitignore вручную
git add -u
git commit -m "Удалила лишний .gitignore из labs/lab2"
```

*Примечание:* В папке `labs/lab2` был создан отдельный `.gitignore`. Позже он был удален, так как корневой 
`.gitignore` уже содержит большую часть необходимых правил для игнорирования файлов сборки, просто в него были 
добавлены новые для игнорирования вспомогательных и выходных файлов.

Все коммиты отправлены в удаленный репозиторий:

```bash
git push origin prog-lab2
```

#### 4.3. Создание Pull Request

На GitHub создан Pull Request:

- **base:** `main`
- **compare:** `prog-lab2`
- **Title:** "Лабораторная работа №2 по структурам данных"
- **Description:** "Код готов к проверке"
- **Reviewer:** преподаватель (vsennov)

#### 4.4. Ожидание ревью и завершение

На данный момент Pull Request ожидает проверки преподавателем. После получения замечаний будут внесены 
исправления в ту же ветку, а после одобрения (Approve) ветка будет слита с `main` и удалена.