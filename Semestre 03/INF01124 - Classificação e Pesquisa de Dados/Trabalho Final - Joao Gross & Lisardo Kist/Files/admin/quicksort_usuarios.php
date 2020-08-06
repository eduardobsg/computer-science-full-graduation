<?php 
//Quick-sorts

//quick sort para ordenação por código da disciplina
function quick_sort_nome ( array $array )
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
        if ( strcmp($value->nome,$pivot->nome) < 0 )
        {
            $smaller[] = $value;
        } 
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
        quick_sort_nome( $smaller ), 
        $same, 
        quick_sort_nome( $larger )
    );
}

//quick sort para arrays de nomes
function quick_sort_user( array $array )
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
		if ( strcmp($value->usuario,$pivot->usuario) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->usuario,$pivot->usuario) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_user( $smaller ), 
        $same, 
        quick_sort_user( $larger )
    );
}

//quick sort para arrays de nomes
function quick_sort_email( array $array )
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
		if ( strcmp($value->email,$pivot->email) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->email,$pivot->email) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_email( $smaller ), 
        $same, 
        quick_sort_email( $larger )
    );
}

//quick sort para arrays de nomes
function quick_sort_status( array $array )
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
		if ( strcmp($value->status,$pivot->status) < 0 )
        {
            $smaller[] = $value;
        } 
		//$value == $pivot 
        elseif ( strcmp($value->status,$pivot->status) == 0 )
        {
            $same[] = $value;
        } 
        else
        {
            $larger[] = $value;
        }
    }    
    return array_merge(
        quick_sort_status( $smaller ), 
        $same, 
        quick_sort_status( $larger )
    );
}

?>