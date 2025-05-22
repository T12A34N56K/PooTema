# PooTema
Tema la Programare Orientata pe Obiect - F.M.I. anul 1. O copie a jocului Gladiabots pe care eu am numit-o Gladiobots.

Pentru prima parte a temei am creat structura de baza pentru scrierea codului unitatilor dar nu am creat o implementare adevarata. Asadar, deocamdata, boti functioneaza bazat pe un cod universal si elementar care se afla in glbAItest.in creat de mine. Gameplay-ul vine din a alege clasele fiecarei unitati si pozitia pe care o sa inceapa meciul. De inceput, jocul este de asemenea inca turn based si in cmdline, cu 160 de runde, dar, pe viitor va fi real time cu grafica 2d.

Regulile temei care sunt respectate sunt urmatoarele:
1. Separarea codului din clase in fisiere header si surse
2. Mostenire: cel putin o clasa de baza cu 3 clase derivate: Bot; Breacher, Mgunner, Riflemen, Sniper
3. Functi virtuale pure: in Bot si in Code
4. Constructori virtuali (clone): in Bot
5. Apelarea constructorilor din clasa de baza din constructori din derivate: in derivatele clasei Bot
6. Clasa cu atribut de tip pointer la o clasa de baza cu derivate: in main() cu Bot, in AI{} cu Bot si Code, in Code{} cu Code
7. Excepti: in functia shoot() din Bot
8. Functii si atribute statice: in Bot, Data si Fread
9. STL: pestetot
10. Cat mai multe const: pe cat cu putinta
11. Functi de nivel inalt: in interiorul lui AI si Code
12. Template: in Fread
13. 2 designe paterns: Data este un Singleton si am un Factory pentru Bot si derivatele sale
