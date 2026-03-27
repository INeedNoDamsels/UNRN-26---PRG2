# 10. Reserva de Butacas

### Variables de entrada (implícitas)
- `mensaje`: Texto que se muestra al usuario al solicitar datos. Es una variable de tipo string.

### Variables de entrada
- `cantidad`: Cantidad de personas para las cuales se desean reservar butacas. Es una variable de tipo `int`.

### Variables internas
- `FILAS`: Cantidad de filas de la sala. Es una constante de tipo int.
- `COLUMNAS`: Cantidad de columnas de la sala. Es una constante de tipo int.
- `sala`: Matriz de tamaño `FILAS x COLUMNAS` que representa el estado de las butacas. Es de tipo int.
  - `0`: butaca libre.
  - `1`: butaca ocupada.
  - `2`: butaca reservada.
- `i`, `j`: Índices utilizados para recorrer la matriz. Son variables de tipo int.
- `f`, `c`: Fila y columna donde se encuentran las butacas disponibles. Son variables de tipo int.
- `contador`: Lleva la cuenta de butacas consecutivas libres. Es una variable de tipo int.
- `input`: Valor ingresado por el usuario en formato string. Es una variable de tipo string.
- `valor`: Variable auxiliar para conversión y generación aleatoria. Es una variable de tipo int.

### Variables de salida (implícito)
- Salida por consola:
  - Representación visual de la sala.
  - Mensajes informativos sobre reservas.
  - Mensajes de error o validación.
- `return 0`: Indica la finalización correcta del programa.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `ingresar()`
- `input ∈ ℤ`.
- `1 ≤ input ≤ 10`.

#### En `mostrar()`
- `sala` deben pertenecer a `{0, 1, 2}`.

#### En `buscarButaca()`
- `cantidad ∈ ℤ`
- `cantidad > 0`
- `cantidad <= COLUMNAS`

---

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** La sala se inicializa con valores aleatorios. Cada butaca será `0` (libre) o `1` (ocupada).

**2.** El programa mostrará el estado de la sala antes y después de cada operación.

**3.** El sistema permitirá reservar butacas consecutivas:
   - Si existen una `cantidad` de butacas libres consecutivas:
     - Se informará la posición encontrada.
     - Las butacas serán marcadas como `2` (reservadas).

**4.** El programa valida la entrada del usuario:
   - Si el valor no es numérico → muestra error.
   - Si el valor está fuera de rango → muestra advertencia.
   - Se seguirá solicitando entrada hasta que sea válida.

**5.** La búsqueda de butacas:
   - Retorna la primera secuencia disponible si existe.
   - Retorna `(-1, -1)` si no encuentra resultados.

**6.** Si no se encuentran butacas suficientes se mostrará un mensaje indicando que no hay suficientes consecutivas disponibles.

**7.** Si no quedan butacas individuales disponibles:
   - Se informará que no hay butacas disponibles.
   - El programa finalizará.


**8.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.