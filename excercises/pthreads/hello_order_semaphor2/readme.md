Modifique su solución de Ejemplo 7 para inicializar todos los semáforos en 0. 
Luego haga que el hilo principal incremente el semáforo del hilo 0. 
¿Produce el mismo resultado que su solución anterior?

R: Sí, si se coloca antes del if (threads && private_data) se comporta de la
misma forma que anteriormente

¿Qué pasa si el hilo principal incrementa el semáforo del hilo 0 después de 
hacer su saludo Hello from main thread?

R: de esta forma nos aseguramos de que el "Hello from main thread" siempre sea 
la primera impresión y elimina el indeterminismo que había anteriormente.