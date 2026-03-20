## 4. El Dígito Verificador
> El programa está diseñado para brindar una solución directa si se proporcionan los argumentos necesarios.

### Variables de entrada (implícitas)
- `argc`: Indica la cantidad de argumentos ingresados por línea de comandos.

### Variables de entrada
- `argv[1]`: Corresponde al primer argumento ingresado por línea de comandos, luego del mismo nombre del programa.
- `codigo`: Es el código ingresado por teclado. Es una variable de tipo string.

### Variables internas
- `intentos`: Indica la cantidad de intentos restantes en caso de un ingreso incorrecto del usuario. Es una variable de tipo int.
- `bandera`: Controla si se usa argumento o entrada manual. Es una variable booleana.
- `digitoVerificador`: Es el último dígito del código procesado, utilizado para su verificación. Es una variable de tipo int.

### Variables de salida (implícito)
- `return <bool>`: Indica si el código ingresado es válido. Es una variable booleana.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `ingresar()`
- `input` ∈ ℤ
- `input` > 0
- La cantidad de caracteres de `input` debe ser igual a 5.
#### En `verificar()`
- Si algún caracter (excepto el último) no es dígito retorna `false`.
#### En `main()`
- `intentos ∈ ℤ`
##### Si se recibe el código como argumento
- `codigo` debe ser un string de longitud 5.

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se realizarán máximo 3 intentos. Luego de ello, se terminará la ejecución del programa.

**2.** Para validar el código, se calculará un "CheckSum" sumando sus dígitos y aplicando el resto de la división por 7.

**3.** El programa separará el cuerpo del código del dígito verificador e indicará si es un código válido.

**4.** Se informará si el código ingresado es correcto o no.
- Si el código es correcto, se imprimirá “*Acceso concedido.*” y termina el programa.
- Si el código es incorrecto y aun no se han terminado los intentos, se imprimirá “*Acceso denegado.*” y se volverá a solicitar la entrada del código.
- Si se terminan los intentos, se imprimirá “*Se ha bloqueado el sistema.*”.

**5.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.