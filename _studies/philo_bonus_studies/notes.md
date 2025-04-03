## Semáforos em C
Similares ao mutex os semáforos controlam o acesso a uma variável compartilhada,
e isso ajuda a prevenir "Race condition" e "Deadlocks"

### Contador interno
O Semáforo mantém um contador interno que representa o número de recuros disponiveis

-> Incrementado (Operação _V_, sem_post()) -> Libera um  recurso.
-> Decrementado (Operação _P_, sem_post()) -> Consome um  recurso.

### Tipos de Semáforo

-> Semáforo Binário(Similar ao mutex, alterna somente entre 0 e 1)
-> Semáforo Contador (Permite múltipla permissões, útil para limitar o acesso 
a um número específico de)

### Sobre
Os semáforos funcionam como um objeto global no processo compartilhado entre todas
as threads

-> sem_open() cria ou abre um semáforo nomeado (???)
-> sem_close() fecha a conexação do processo com o semáforo
-> sem_unlink() remove o semáforo do sistema

### sem_close VS sem_unlink
sem_close -> remove o semáforo do processo atual
sem_unlink -> remove o semáforo do sistema, impedindo novo acessos

## Volatile e Mutex
O Volatile é um tipo em C que garante que aquela variável sempre vai ser lida
de forma atualizada no processo, isso garante que os processos não tenham 
comportamento indefinidos ou loops infinitos quando passam por processos de 
otimização do compilador. O valor sempre será lido diretamente da memória
porem ele não protege contra acessos concorrentes de múltiplas threads.

sincronização entre threads é efetuada por mutex;

## POSIX

POSIX sigla para *Portable Operating System interface*
é um conjunto de padrões definidos pelo IEEE para garantir compatibilidade 
entre sistemas operacionais baseados em Unix. Ele especifica interfaces de
programação de aplicativos (APIs), shells e utilitários de linha de comando,
além de outros aspectos como manipulação de processos, threads e arquivos.

O objetivo do POSIX é facilitar a portabilidade de software entre diferentes
sistemas operacionais, garantindo que um programa escrito para um sistema 
compatível com POSIX possa ser facilmente adaptado para rodar em outro

---

✅ volatile

Evita otimizações do compilador.
Garante que a variável sempre seja lida diretamente da memória.
Não impede condições de corrida em threads ou processos.

✅ mutex (pthread_mutex_t)

Garante exclusão mútua entre threads do mesmo processo.
Não funciona entre múltiplos processos (não é automaticamente compartilhado entre eles).

✅ semáforo (sem_t)

Semelhante ao mutex, mas pode ser compartilhado entre múltiplos processos (funciona com fork()).
Permite controle de múltiplos acessos simultâneos (exemplo: limitar 3 processos acessando um recurso).