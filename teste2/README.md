nome: Gabriel Henriques Siqueira    ra: 155446

# MC714 - Teste 2

## Estrategia de implementação

        Um script foi usado para criar 1000 processos, cada processo é um
    programa em python que faz o papel de cliente e servidor. 
        Para diferenciação cada processo recebe um numero (num) de 0 a 1000
    que sera seu identificador. O processo que recebe o numero 0 é o processo
    inicial.
        Todos os processos executam a função servidor, onde eles abrem um
    socket na porta 5000 + num para aguardar o recebimento de alguma mensagem.
        Uma vez que um processo receba a mensagem ele inicia uma nova thread
    com a função cliente, esta função tenta se conectar com alguma porta
    aleatória no intervalo 5000 e 5000 + N (onde N é o numero de
    processos que é passado como parâmetro) e enviar a mensagem.
        O processo servidor ao receber uma mensagem retorna uma nova mensagem
    informando se já conhecia ou não a mensagem. Caso o cliente já conheça a
    mensagem o servidor gera um numero aleatória de 0 a K (valor passado como
    parâmetro), se este valor for 0 o cliente para de executar e o processo
    fica só como servidor.
        Todos os processos terminam ao receberem o sinal de timout quando
    estiverem muito tempo esperando uma conexão.

## Resultados

### Tentativas

        Um contador no processo cliente foi usado para contar o numero de
    tentativas, quando o processo termina ele imprime o contador.

            K = 4: mínimo: 1, máximo: 22, média: 4.8532206969377
            K = 5: mínimo: 1, máximo: 40, média: 5.80680680680681
            K = 6: mínimo: 1, máximo: 37, média: 6.54909819639279
            K = 7: mínimo: 1, máximo: 48, média: 7.72545090180361
            K = 8: mínimo: 1, máximo: 47, media: 8.564

        Como esperado vemos que o numero de tentativas aumenta com K.

### Sucessos

    Também foram medidos com um contador.

            K = 4: mínimo: 0, máximo: 9, média: 0.993664202745512
            sucesso/tentativas(médias): 0.2047432550043515
            K = 5: mínimo: 0, máximo: 6, média: 0.997997997997998
            sucesso/tentativas(médias): 0.17186691949663843
            K = 6: mínimo: 0, máximo: 5, média: 0.998997995991984
            sucesso/tentativas(médias): 0.15253977968176247 
            K = 7: mínimo: 1, máximo: 5, média: 0.998997995991984
            sucesso/tentativas(médias): 0.12931258106355378
            K = 8: mínimo: 0, máximo: 7, média: 0.999
            sucesso/tentativas(médias): 0.11665109761793555

    Assim como nas tentativas vemos um aumento esperado com o aumento do K.

### Processos com o informação

        Todos os resultados dos marcadores foram salvos em um arquivo um por
    linha então depois dos clientes todos terminarem de mandar mensagem o
    numero de linhas deste arquivo corresponde ao numero de processos com a
    mensagem.

            K = 4: 947
            K = 5: 999
            K = 6: 998
            K = 7: 998
            K = 8: 1000

        Vemos que o numero de processos se mantem aproximadamente constante,
    mas K = 4, teve a pior disseminação e K = 8 foi o único onde todos os
    processos terminaram com a mensagem.

### Tempo até estabilizar

        Foram usados os tempos de acesso (o ultimo tempo de acesso foi quando
    o arquivo foi criado pelo script) e de mudança (quando o ultimo
    cliente inseriu os dados) dos arquivos de saída.
            K = 4: 3m 15.117542325s
            K = 5: 1m 57.363869544s
            K = 6: 1m 54.400521957s
            K = 7: 2m 5.407201183s
            K = 8: 2m 3.307193338s
