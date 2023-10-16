# pa-prysyazhnyy-and

Щоб збудувати проект потрібно:
	1) Склонувати репозиторій
	2) Відкрити командний рядок розробника (Пошук -> Developer Command Prompt for VS або у Visual Studio відкрити Tools -> Command Line -> Developer Command Prompt)
	3) Змінити локацію на ...\pa-prysyazhnyy-and\src\Lab*
	4) Ввести команду msbuild Lab*.sln /p:Configuration=Debug

Коли проект збудовано, у папці ...\pa-prysyazhnyy-and\src\Lab*\x64\Debug запустити Lab*.exe

Щоб запустити тести потрібно:
	1) Збудувати проект
	2) Через командний рядок розробника зайти у папку ...\pa-prysyazhnyy-and\src\Lab*\x64\Debug
	3) Ввести команду vstest.console.exe Lab*_tests.dll

Замість * потрібно підставити відповідний номер лабораторної роботи (1, 2, 3 ...)