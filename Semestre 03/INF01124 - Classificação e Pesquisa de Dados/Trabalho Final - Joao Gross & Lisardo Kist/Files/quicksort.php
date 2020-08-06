<?php 
//Quick-sorts

//quick sort para ordenação por código da disciplina
function quick_sort_ano( array $array )
{
    // Caso trivial
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
        if ( strcmp($value->ano,$pivot->ano) < 0 )
        {
            $smaller[] = $value;
        } 
        elseif ( strcmp($value->ano,$pivot->ano) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_ano( $smaller ), 
        $same, 
        quick_sort_ano( $larger )
    );
}

//quick sort para arrays de nomes
function quick_sort_prof( array $array )
{
    // Caso trival
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso, primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
		//value < pivot
		if ( strcmp($value->professor,$pivot->professor) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->professor,$pivot->professor) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_prof( $smaller ), 
        $same, 
        quick_sort_prof( $larger )
    );
}

//quick sort para arrays de nomes
function quick_sort_cadeira( array $array )
{
    // Caso trival
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso, primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
		//value < pivot
		if ( strcmp($value->nome,$pivot->nome) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->nome,$pivot->nome) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_cadeira( $smaller ), 
        $same, 
        quick_sort_cadeira( $larger )
    );
}

function quick_sort_cod( array $array )
{
    // Caso trival
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso, primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
		//value < pivot
		if ( strcmp($value->cod,$pivot->cod) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->cod,$pivot->cod) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_cod( $smaller ), 
        $same, 
        quick_sort_cod( $larger )
    );
}

function quick_sort_area( array $array )
{
    // Caso trivial
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
        if ( strcmp($value->area, $pivot->area) < 0 )
        {
            $smaller[] = $value;
        } 
        elseif ( strcmp($value->area, $pivot->area) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_area( $smaller ), 
        $same, 
        quick_sort_area( $larger )
    );
}

function quick_sort_tamanho( array $array )
{
    // Caso trivial
    if ( count( $array ) <= 1 )
    {
        return $array;
    }
    // Pivô qualquer (no caso primeiro elemento)
    $pivot = reset($array);
    $same = array();
    $larger = array();
    $smaller = array();

    foreach ( $array as $value )
    {
        if ( (integer)$value->tamanho < (integer)$pivot->tamanho )
        {
            $smaller[] = $value;
        } 
        elseif ( (integer)$value->tamanho == (integer)$pivot->tamanho )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_tamanho( $smaller ), 
        $same, 
        quick_sort_tamanho( $larger )
    );
}

?>