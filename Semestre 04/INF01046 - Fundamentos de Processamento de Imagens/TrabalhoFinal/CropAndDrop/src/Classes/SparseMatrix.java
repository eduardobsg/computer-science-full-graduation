package Classes;

import java.util.LinkedList;
import java.util.Stack;

/**
 * Matrizes esparsas são aquelas cuja maioria dos elementos tem valor nulo.
 * Por lidarmos com matrizes muito grandes, optamos por esta implementação que economiza memória.
 * Esta classe lida com dois tipos de dados: orientado a inserções e orientado a buscas.
 * Uma variável booleana (dataType) decide qual dos tipos é usado.
 *
 * IMPORTANTE: Não deve-se fazer uso de inserções e buscas misturadas com esta classe.
 *             Cada troca inserção/busca implica a troca do tipo de dados, que é de alta complexidade.
 */
public class SparseMatrix {


    private static final boolean INSERTIONS_DATA_TYPE = true; //Constante para indicar se o tipo de dados para inserções está sendo usado.
    private static final boolean SEARCHES_DATA_TYPE = false; //Constante para indicar se o tipo de dados para buscas está sendo usado.
    private boolean dataType = INSERTIONS_DATA_TYPE; //Indica o tipo de dados usado.

    private LinkedList matrix; //A matriz que está sendo usada.
    
    //Orientado a inserções
    private LinkedList matrix_insertions = new LinkedList(); //Guarda informações sobre a matriz. Usa o tipo de dados de inserções.
    //Orientado a buscas.
    private LinkedList matrix_searches = new LinkedList(); //Guarda informações sobre a matriz. Usa o tipo de dados de buscas.
    private int[] rows_index; //Índice para as linhas da matriz em matrix_searches. Usa o tipo de dados de buscas.
    private static final int ROW_WITHOUT_ELEMENTS = -1; //Em rows_index, indica se uma linha não possui elementos. Usa o tipo de dados de buscas.
    private int[] rows_element_number; //Assim como rows_index, porém contém a informação do número de elementos armazenados em cada linhas. Usa o tipo de dados de buscas.

    private int numberOfStoredElements; //O número de elementos que a matriz possui armazenados.
    private int width; //Comprimento da matriz, considerando dados omitidos.
    private int height; //Altura da matriz, considerando dados omitidos.


    /**
     * Construtor.
     * Passa o comprimento e altura da matriz, que consideram dados omitidos.
     */
    public SparseMatrix(int _width, int _height){
        width = _width;
        height = _height;
        matrix = matrix_insertions;
        dataType = INSERTIONS_DATA_TYPE;
    }

    //General data about this matrix.
    public int getHeight(){
        return height;
    }
    public int getWidth(){
        return width;
    }

    //Para medições de eficiência.
    public int getLength(){
        return width*height;
    }
    public int getStoredLength(){
        return numberOfStoredElements;
    }

/*-------------------------------------
 *             INSERÇÕES ~ Tipo de dados orientado a inserções
 * A estrutura de dados é como segue:
 *
 *   (i) As linhas são representadas por uma LinkedList.
 *   (ii) Colunas não são diferenciadas na estrutura, mas sim dentro dos elementos.
 *   (iii) Cada elemento é uma pilha de três elementos (x, y, valor).
 *
 * Assim, representando lista por () e pilha por {}, a matriz à seguir seria representada como:
 *
 *     | 1 0 0 |
 * A = | 2 1 0 |
 *     | 0 0 0 |
 *
 * ({0,0,1},{0,1,2},{1,1,1})
 *
 * Esta implementação é útil para inserções, mas ruim para buscas.
 * A lista não é ordenada.
-------------------------------------*/
    /**
     * Insere um elemento com os índices indicados na matriz.
     * A inserção é no tipo de dados descrito no acima.
     */
    public void insert(int _x, int _y, int _value){
        if(dataType != INSERTIONS_DATA_TYPE){
            convertDataTypeToInsertOriented();
        }
       doInsert(_x, _y, _value);
    }
    private void doInsert(int _x, int _y, int _value){
        Stack<Integer> element = assembleElement(_x, _y, _value);
        matrix.addLast(element);
        numberOfStoredElements++;
    }
    /**
     *  Função para montar um elemento à partir de seus dados.
     */
    private Stack<Integer> assembleElement(int _x, int _y, int _value){
        Stack<Integer> element = new Stack<Integer>();

        element.push(_value);
        element.push(_y);
        element.push(_x);

        return element;
    }
    /**
     * Converte os dados em matrix_insertions para matrix_searches.
     * O tipo de dados mudará para o descrito no cabeçalho das buscas.
     */
    private void convertDataTypeToSearchOriented(){
        if(dataType != SEARCHES_DATA_TYPE){
            matrix = matrix_searches;
            doConvertToSearchOriented();
        } 
    }
    private void doConvertToSearchOriented(){
        int lastMatrixIndexChecked = 0;
        int lastIndexInsertedIntoSearch = 0;
        int elementRow;
        Stack<Integer> element;
        boolean firstElementOfRowFound = false;
        boolean foundElementOfRow = false;
        boolean checkedAllElements = false;

        rows_index = new int[getHeight()];
        rows_element_number = new int[getHeight()];
        for(int _elementIndex = 0; _elementIndex < getHeight(); _elementIndex++){
            element = (Stack<Integer>) matrix_insertions.get(_elementIndex);
            elementRow = getElementRow(element);
            insertIntoSearchDataType(elementRow, element);
        }
        
    }
    

/*-------------------------------------
 *             BUSCAS ~ Tipo de dados orientado a buscas
 * A estrutura de dados é como segue:
 *
 *   (i) As linhas são representadas por uma LinkedList ordenada pelo valor row de seus elementos (o segundo valor em cada elemento).
 *   (ii) Colunas não são diferenciadas na estrutura, mas sim dentro dos elementos.
 *   (iii) Cada elemento é uma pilha de três elementos {x, y, valor}.
 *   (iv) Há um array que permite acesso rápido às linhas, que funciona como descrito à seguir.
 *
 * Assim, representando lista por (), pilha por {} e array por [], a matriz à seguir seria representada como:
 *
 *     | 1 0 0 |
 * A = | 2 1 0 |
 *     | 0 0 0 |
 *
 * ({0,0,1},{0,1,2},{1,1,1}), [0 => 0, 1 => 1, 2 => -1]
 *
 * Esta implementação é útil para buscas, mas ruim para inserções.
-------------------------------------*/
    /*
    public int get(int _x, int _y){
        if(dataType != SEARCHES_DATA_TYPE){
            matrix = matrix_searches;
            dataType = SEARCHES_DATA_TYPE;
            convertDataTypeToSearchOriented();
        }
        
    }
     
     */

    /**
     * Insere um elemento no tipo de dados orientado a buscas.
     * Por questões de eficiência, deve ser usado somente por esta classe, em conversões de tipo.
     */
    private void insertIntoSearchDataType(int _row, Stack<Integer> _element){
        int numberOfElementsOnRow;
        int numberOfElementsOnPreviousRow;

        if(_row != 0){
            if(rows_index[_row] == ROW_WITHOUT_ELEMENTS){ //A posição deste elemento será usada.
                numberOfElementsOnPreviousRow = rows_element_number[_row - 1];
                rows_index[_row] = rows_index[_row - 1] + numberOfElementsOnPreviousRow;
            } //Caso contrário, mantém-se a posição presente.
        } else {
            rows_index[0] = 0;
        }

        //Insere o elemento e atualiza a lista.
        numberOfElementsOnRow = rows_element_number[_row];
        matrix_searches.add(rows_index[_row] + numberOfElementsOnRow, _element);

        rows_element_number[_row]++;
        for(int row = _row + 1; row < getHeight(); row++){
            rows_index[row]++;
        }
    }

    /**
     * Retorna o índice no eixo x do elemento parâmetro na matriz.
     */
    private int getElementColumn(Stack<Integer> _element){
        return (int) _element.peek();
    }
    /**
     * Retorna o índice no eixo y do elemento parâmetro na matriz.
     */
    private int getElementRow(Stack<Integer> _element){
        int elementX = _element.pop();
        int elementY = _element.peek();
        _element.push(elementX);
        return (int) elementY;
    }
    /**
     * Retorna o valor do elemento parâmetro na matriz.
     */
    private int getElementValue(Stack<Integer> _element){
        int elementX = _element.pop();
        int elementY = _element.pop();
        int elementValue = _element.peek();
        _element.push(elementY);
        _element.push(elementX);
        return elementValue;
    }
    /**
     * Converte os dados em matrix_searches para matrix_insertions.
     * O tipo de dados mudará para o descrito no cabeçalho das inserções.
     */
    private void convertDataTypeToInsertOriented(){
        if(dataType != INSERTIONS_DATA_TYPE){
            matrix = matrix_insertions;
            matrix_insertions = matrix_searches;
        }
    }

   

}
