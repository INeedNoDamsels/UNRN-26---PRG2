# 7. Optimización de Stock
### Variables de entrada (implícitas)
- Entrada por teclado mediante la función `ingresar()`: opción de menú elegida por el usuario.

---

### Variables de entrada
- `input`: Cadena ingresada por el usuario que representa la opción del menú. Es una variable de tipo string.
- `valor`: Opción convertida a entero desde `input`. Es una variable de tipo int.
- `min`, `max`: Indica los límites para la generación de números aleatorios en `obtener()`. Son variables de tipo int.

---

### Variables internas
- `bandera`: Controla la ejecución del bucle principal. Es una variable booleana.
- `productos[3]`: Arreglo de objetos `Producto` con atributos `nombre` y `precioUnitario`. Variables de tipo string y float, correspondientemente.
- `items[3]`: Arreglo de objetos `Inventario` con atributos `producto`, `cantidad` y `puntoCritico`. 
- `miNegocio`: Objeto de tipo `Negocio` que gestiona `saldo`, `deuda` y el inventario `items`. Variables de tipo float.
- `i`: Índice para recorrer arreglos. Es una variable de tipo int.
- `vendidas`: Indica la cantidad de unidades vendidas en una transacción. Es una variable de tipo int.
- `precioVenta`: Indica el precio de venta con un margen del 30% aplicado. Es una variable de tipo float.
- `ganancia`: Indica el monto total obtenido por la venta de un producto. Es una variable de tipo float.
- `total`: Indica el costo total de reposición en `realizarPedido()`. Es una variable de tipo float.

---

### Variables de salida (implícito)
- Salida por consola:
  - Menú de opciones.
  - Estado del inventario (`mostrarStock()`).
  - Información de ventas.
  - Costo de pedidos y reposición.
  - Mensajes de atención a clientes o cierre de sesión.
- `return 0`: indica la finalización correcta del programa.  

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `ingresar()`
- `input ∈ ℝ`
- `valor > 0`.

#### En `Inventario`
- `cantidad >= 0`.
- `puntoCritico >= 0`.

#### En `Negocio`
- `saldo ≥ 0`.

---

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** El programa gestiona un inventario de 3 productos (`Pan`, `Leche`, `Huevos`) con cantidades iniciales aleatorias.

**2.** El usuario puede seleccionar opciones de menú:
   - **1. Actualizar stock** donde se muestra el inventario y señala si algún producto necesita reposición.
   - **2. Realizar pedido** donde se repone automáticamente productos bajo el punto crítico, calcula costo total, ajusta saldo y deuda.
   - **3. Salir** donde finaliza la ejecución del programa.
   - **Otro valor** donde simula ventas aleatorias de productos, actualiza inventario y saldo/deuda.

**3.** En la función `vender()`:
   - Se selecciona un producto aleatorio.
   - Se determina la cantidad vendida aleatoriamente.
   - Se calcula ganancia con margen.
   - Se actualizan `cantidad`, `saldo` y `deuda` según corresponda.

**4.** En la función `realizarPedido()`:
   - Cada producto que necesita reposición se repone automáticamente.
   - Se aplica costo total y ajuste de saldo/deuda.
   - Si la cantidad repuesta > 50 el costo fijo queda bonificado.

**5.** Todas las operaciones mantienen consistencia de inventario y finanzas del negocio.

**6.** El programa terminará de manera controlada, ejecutando un return 0 si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente. 