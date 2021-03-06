<?php
/*******************************************************
 * Copyright (C) 2014 Armel Koudoum <dev.goldprint@gmail.com>
 * 
 * This file is part of Jungle Lion.
 * 
 * Jungle Lion can not be copied and/or distributed in any way without the express
 * permission of Armel Koudoum
 *******************************************************/

function membership_admin_fieldslist() {
	$header = array(
      'field_weight' => array('data' => t('Weight'), 'field' => 's.field_weight', 'sort' => 'asc'),
	    'field_label' => array('data' => t('Label'), 'field' => 's.field_label'),
	    'field_id' => array('data' => t('Field Id'), 'field' => 's.field_iden'),
	    'field_type' => array('data' => t('Field type'), 'field' => 's.field_type'),
	    'r_field' => array('data' => t('For registration'), 'field' => 'u.actif_signup'),
	    'p_field' => array('data' => t('For profile'), 'field' => 'u.actif_profile'),
	    'o_field' => array('data' => t('For Order'), 'field' => 'u.actif_order'),
	    'operations' => array('data' => t('Operation')),
	    /*
      'up' => array('data' => t('MOve')),
	    'down' => array('data' => t('Move')),
      */
      'required' => array('data' => t('Required')),
	  	);
	$options = array();
	$query = db_select('jl_signupfields', 's');

	$query
    ->fields('s', array('field_id', 'field_label', 'field_iden', 'field_type', 'actif_signup','actif_profile','actif_order','field_weight', 'required_field'))
    ->orderBy('field_weight', 'ASC');
    
  	$result = $query->execute();

  	$state = array("No", "Yes");
  	$destination = drupal_get_destination();
  	$maxweight = 0;

  	foreach($result as $field) {
  		if($maxweight < $field->field_weight)
  			$maxweight = $field->field_weight;
  		$options[$field->field_id] = array(
        'field_weight' => array('data' => array( 
            '#type' => 'textfield',
            '#title' => t('Weight for @title', array('@title' =>  $field->field_label)),
            '#title_display' => 'invisible',
            '#default_value' => $field->field_weight,
            '#size' => 1,
            '#attributes' => array(
                      'class' => array('field-weight'), 
                      'value' => array($field->field_weight), 
                      'style' => array('width:20px'),
                      'readonly' => array('readonly'),
                      'name' => array('weight['.$field->field_id.']'),
                      ),
            '#disabled' => true,
          )
        ),
  			'field_label' => $field->field_label,
  			'field_id' => $field->field_iden,
  			'field_type' => $field->field_type,
  			'r_field' => array('data' => array('#type' => 'link', '#title' => $state[$field->actif_signup], '#href' => "membership/changestate/$field->field_id/$field->actif_signup/signup", '#options' => array('query' => $destination))),
  			'p_field' => array('data' => array('#type' => 'link', '#title' => $state[$field->actif_profile], '#href' => "membership/changestate/$field->field_id/$field->actif_profile/profile", '#options' => array('query' => $destination))),
  			'o_field' => array('data' => array('#type' => 'link', '#title' => $state[$field->actif_order], '#href' => "membership/changestate/$field->field_id/$field->actif_order/order", '#options' => array('query' => $destination))), 
  			'operations' => array('data' => array('#type' => 'link', '#title' => t('edit'), '#href' => "admin/membership/field/$field->field_id/edit", '#options' => array('query' => $destination))),
  			/*
        'up' => array('data' => array('#type' => 'link', '#title' => t('up'), '#href' => "membership/movefield/$field->field_id/up/$field->field_weight", '#options' => array('query' => $destination))),
  			'down' => array('data' => array('#type' => 'link', '#title' => t('down'), '#href' => "membership/movefield/$field->field_id/down/$field->field_weight", '#options' => array('query' => $destination))),
        */
        'required' => array('data' => array('#type' => 'link', '#title' => $state[$field->required_field], '#href' => "membership/setrequired/$field->field_id/$field->required_field", '#options' => array('query' => $destination))),
  			);
  	}
  	//print_r($field_list);
  	$keyslist = array_keys($options);

  	$last_elt = end($keyslist);

  	$options[$keyslist[0]]['up'] = array('data' => array());
  	$options[$last_elt]['down'] = array('data' => array());

  	$form['formfields'] = array(
	    '#type' => 'tableselect',
	    '#header' => $header,
	    '#options' => $options,
	    '#empty' => t('No field available.'),
      '#prefix' => '<div class="messages warning listtable" style="display:none">'.t('You should submit to save your changes.').'</div>',
	  	);
  	
    $form['submit_btn'] =  array( 
    '#type' => 'submit', 
    '#value' => t('Save changes'), 
    );
    //$form["#validate"][] = "membership_admin_fieldslist_validate";
    $form['#submit'][] = 'membership_admin_fieldslist_submit';
  	return $form;
}

function membership_admin_fieldslist_submit($form, &$form_state) {
  $form_rows = $_POST['weight'];

  foreach($form_rows as $key => $val) {
      db_update('jl_signupfields') 
        ->fields(array( 'field_weight' => $val, )) 
        ->condition('field_id', $key, '=') 
        ->execute();
    }
    drupal_set_message(t('The changes have been saved.'));
}

function membership_setrequired($field, $state) {
  $num_updated = db_update('jl_signupfields') 
        ->fields(array( 
        'required_field' => ($state==0?1:0), 
        )) 
        ->condition('field_id', $field, '=') 
        ->execute(); 

  drupal_goto("admin/membersh");
}
