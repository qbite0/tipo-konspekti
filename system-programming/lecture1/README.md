---
начат: 03.09.2022
закончен: 07.09.2022
тема: Синхронизация потоков в пользовательском режиме Windows
---

# Синхронизация потоков в пользовательском режиме *Windows*
**Процессом** (*process*) называется экземпляр программы, загруженной в память.
Все потоки имеют доступ к системным ресурсом (к кучам, последовательным портам). Если один из потоков запросит монопользовательский доступ к какому либо ресурсу другим потокам, которым необходим этот ресурс не удасться выполнить эту задачу. Для того чтобы потоки могли взаимодействовать друг с другом происходит системы синхронизации.

Потоки должны взаимодействовать друг с другом в двух основных случаях:
* совместно используя разделяемый ресурс (чтобы не разрушить его);
* когда нужно уведомлять другие потоки о завершении каких-либо операций

Средства для синхронизации в *Windows*
1) **Атомарный доступом** (*atomic access*) — монопольным захватом ресурса обращающимся к нему потоком.
2) Распределение адресного пространства между потоками с помощью системных функций, которые гарантируют монопольное изменение функций.
3) .... независимо от того как сгенерирован код и сколько процессоров установлено в компьютере.

Функции для синхронизации
* InterlockedExchangeAdd
* InterlockedCompareExchange 32 рязрядная
* InterlockedCompareExcbangePointer 64 разрядная
* SwitchToThread

# Алгоритм Петерсона
**Алгоритм Петерсона** – это программный алгоритм взаимного исключения потоков без запрещения прерываний. Он был предложен в 1981 году Гарри Петерсоном из университета Рочестер (США). В основу алгоритма Петерсона лег алгоритм Деккера. Изначально алгоритм был сформулирован для 2-поточного случая, но он может быть обобщен для произвольного количества потоков. Алгоритм не основан на использовании таких команд процессора, которые запрещают прерывания, блокировки шины памяти, в нём используются только общие переменные памяти и цикл ожидания входа в критическую секцию кода, поэтому условно алгоритм называют программным. Алгоритм Петерсона учитывает отсутствие атомарности в операциях чтения и записи переменных и может применяться без использования команд управления прерываниями.

Алгоритм работает следующим образом: у каждого процесса есть своя переменная flag[i] и общая переменная turn. Хранение всех переменных происходит в общей памяти. Факт захвата ресурса запоминается в переменной flag , в переменной turn – номер захватившего ресурс процесса.

Когда исполняется пролог критической секции, процесс Pi заявляет о готовности к выполнению критического участка и сразу предлагает другому процессу приступить к его выполнению. В случае, когда оба процесса подошли к прологу единовременно, они оба объявят о своей готовности и предложат друг другу выполняться. При этом каждое предложение следует друг за другом. Тем самым работу в критическом участке продолжит процесс, которому было сделано последнее предложение.

Нить выполняется:
1) когда ей выделено процессорное время, т.е. она может находиться в *состоянии активности*.
2) может быть неактивной и ожидать выделения процессора, т.е. быть в *состоянии готовности*.
3) *состояние блокировки*

Несинхронизированная работа нитей: если временно приостановить выполнение нити вывода на экран (пауза), фоновая нить заполнения массива будет продолжать работать.

Объекты синхронизации
* Взаимоисключение (mutex)
* Критическая секция (critical section)
* Событие (event)
* Семафор (semaphore)

# Взаимоисключение (Mutex)
позволяют координировать доступ к разделяемому ресурсу. Сигнальное состояние объекта (т.е. состояние "установлен") соответствует моменту времени, когда объект не принадлежит ни одной нити и его можно "захватить". И наоборот, состояние "сброшен" (не сигнальное) соответствует моменту, когда какая-либо нить уже владеет этим объектом. Доступ к объекту разрешается, когда нить, владеющая объектом, освободит его.
Две (или более) нити могут создать мьютекс с одним и тем же именем, вызвав функцию CreateMutex. Первая нить действительно создает мьютекс, а следующие - получают дескриптор уже существующего объекта. Это дает возможность нескольким нитям получить дескриптор одного и того же мьютекса, освобождая программиста от необходимости заботиться о том, кто в действительности создает мьютекс. Если используется такой подход, желательно установить флаг bInitialOwner в FALSE, иначе возникнут определенные трудности при определении действительного создателя мьютекса.

# Симафор
**Семафор** - примитив синхронизации работы процесса и потока в основе которого лежит счётчик над которым можно производить 2 атомарные операции увеличение и уменьшения значения на 1. Данный объект позволяет "захватить" себя определенному количеству нитей. После этого "захват" будет невозможен, пока одна из ранее "захвативших" семафор нитей не освободит его. Есть внутренее состояние. Двоичный семафор блокирует поток когда это необходимо.

* Двоичные 
* Вычислительный

Мьютексный семафор выполняют работы аналогичную двоичным с исключением что не передаются в другие потоки.

Стандартная библиотека имеет вычислительные и двоичные семафоры. Семафоры нельзя копировать и перемещать. Они часто используются для реализации уведомлений. Метод реализации (по умолчанию данное значение равно 1)

## Применение
Семафоры применяются для ограничения количества нитей, одновременно работающих с ресурсом. Объекту при инициализации передается максимальное число нитей, после каждого "захвата" счетчик семафора уменьшается. Сигнальному состоянию соответствует значение счетчика больше нуля. Когда счетчик равен нулю, семафор считается не установленным (сброшенным).
## Функции
*CreateSemaphore* - создает объект-семафор с указанием и максимально возможного начального его значения
*OpenSemaphore* – возвращает дескриптор существующего семафора, захват семафора производится с помощью ожидающих функций, при этом значение семафора уменьшается на единицу, ReleaseSemaphore - освобождение семафора с увеличением значения семафора на указанное в параметре число.

# Критическая секция
Выделить участок кода, где нить получает доступ к разделяемому ресурсу, и предотвратить одновременное использование ресурса. Перед использованием ресурса нить входит в критическую секцию. Если после этого какая-либо другая нить попытается войти в ту же самую критическую секцию, ее выполнение приостановится, пока первая нить не покинет секцию. Используется только для нитей одного процесса. Порядок входа в критическую секцию не определен.
## Функции
*EnterCriticalSection* - выполняется когда нить входит в критическую секцию
*LeaveCriticalSection* - выполняется когда нить выходит из критической секции
*TryEnterCriticalSection* - проверяет, занята ли критическая секция в данный момент. С ее помощью нить в процессе ожидания доступа к ресурсу может не блокироваться, а выполнять какие-то полезные действия.

# Условные переменные
Не имеют внутренее состояние

# Блокировка
Блокировки чтения и записи - позволяет читать много потоков при этом операции чтения или записи не могут быть выполнены одновременно.

# Барьеры
Это механизм синхронизации позволяющие останавлитвать выполнения группу потоков пока эти потоки не дойдут до опредеённой точки выполнения почмечаймы функцией ожидания барьер При создании браьер получает целое положительное число, которое показыавть кол-ов потоков в этой группы. Поток ожидающий на браьере останавливаетьс пока общее кол-во поток ожиающих на это браьере не станет равным нул.
Барьер для группы потоков в исходном коде означает что каждый поток должен остановиться в этой точке и подождать достижения этим потоком. Барьер определяется 
1) уменьшающий счётчик
2) блокирующий 
3) проверка на 0
4) уменьшение счётчика на 1 по умолчанию

# Сообщения 
В распределенных системах, состоящих из нескольких процессоров, каждый из которых имеет собственную оперативную память, блокирующие переменные, се­мафоры, сигналы и другие аналогичные средства, основанные на разделяемой памяти, оказываются непригодными. В таких системах синхронизация может быть реализована только посредством обмена сообщениями.

# Защёлка
Механизм синхронизации потоков который позволяет любое колво потоков пока ожидаемое колво потоков не достигнет барьера.нельзя использовать повторно. данные механизмы когда выполнение алгоритма можно раздедить на несколько этапов в частности с помощью барьера можно организовать точку сбора в которой можно организовать точку результатов.