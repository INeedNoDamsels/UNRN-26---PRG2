## 1. El Costo de la Infraestructura
> El programa está diseñado para brindar una solución directa si se proporcionan los argumentos necesarios.

### Variables de entrada (implícitas)
- `argc`: Indica la cantidad de argumentos ingresados por línea de comandos.

### Variables de entrada
- `argv[1]` y `argv[2]` corresponden al primer y segundo argumento ingresado por línea de comandos, luego del mismo nombre del programa.
- `terreno[0]`: Indica el ancho, en metros, del terreno. Es una variable de tipo float.
- `terreno[1]`: Indica el largo, en metros, del terreno. Es una variable de tipo float.

### Constantes
- `costos[2]`: Precio de metro lineal, dependiendo del tipo de cableado. Es un arreglo de 2 elementos, cada uno de tipo float.

### Variables de salida
- `valores[0]`: Indica el costo de cablear por el borde de un terreno de **X**×**Y** mts. de área. Es una variable de tipo float.
- `valores[1]`: Indica el costo de cablear por la diagonal de un terreno de **X**×**Y** mts. de área. Es una variable de tipo float.
- Se imprime un mensaje en pantalla indicando el tipo de cableado más conveniente en relación al coste.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `ingresar()`
- `valor` ∈ ℝ
- `valor` > 0
#### En `main()`
- `terreno[0] > 0` y `terreno[0] ∈ ℝ`
- `terreno[1] > 0` y `terreno[1] ∈ ℝ`
- `costos[0] > 0` y `costos[0] ∈ ℝ`
- `costos[1] > 0` y `costos[1] ∈ ℝ`
- `argc == 3`
- `argv[1] ∈ ℝ`
- `argv[2] ∈ ℝ`

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se calculará correctamente el coste de cada tipo de trabajo a realizar.
- `valores[0]` = `costos[0]` × (`terreno[0]` + `terreno[1]`)
- `valores[1]` = `costos[1]` × **√(**`terreno[0]` + `terreno[1]`**)**

**2.** Se informará el tipo de cableado más económico.
- Si `valores[0] < valores[1]`, se imprimirá “*por el borde*”.
- Si `valores[0] > valores[1]`, se imprimirá “*en diagonal*”.

**3.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.