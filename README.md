# Combinaciones
Este programa se ha creado a raiz de resolver el problema de [formar N numero usando M veces el número P](https://matematicascercanas.com/2019/01/02/jugando-con-numeros-2019-2/).

Por ejemplo, obtener el 5 (N) usando tres (M) cuatros (P). El resultado de este seria 4+(4/4). Fijaos que se estan usando tres cuatros, y el resultado de la operación da 5.

El objetivo era obtener el 2019 usando siete treses, y después de horas calculandolo y mucho tiempo de ejecución obtuve el resultado (3+3)!+3+[(3+3)^3]*3!

> /!\\ Por tal de optimizar al máximo el tiempo todo se guarda a la RAM. Tened en cuanta que es exponencial; cuanto mayor sea la M (números a usar) muchas más combinaciones que comprobar. Con una M de 6 no espereis que la RAM baje de los 128GB.

Para ejecutar el compilado usad "./combinaciones P M N", siendo P, M y N los mencionados ya anteriormente.
