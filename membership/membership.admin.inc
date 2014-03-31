<?php
/*******************************************************
 * Copyright (C) 2014 Armel Koudoum <dev.goldprint@gmail.com>
 * 
 * This file is part of Jungle Lion.
 * 
 * Jungle Lion can not be copied and/or distributed in any way without the express
 * permission of Armel Koudoum
 *******************************************************/

function membership_admin_settings() {

    $form['disclaimer'] = array( 
	    '#prefix' => '<h2>', 
	    '#markup' => t('Create a new field for your subscription form.'), 
	    '#suffix' => '</h2>', 
    ); 
	$form['field_label_name'] = array(
		'#type' => "textfield",
		'#title' => t("Field label : "),
		'#description' => t("Enter the label name of the new field"),
		'#size' => 50,
		//'#required' => TRUE,
		);
	//
	$form['field_id_name'] = array(
		'#type' => "textfield",
		'#title' => t("Field ID : "),
		'#description' => t("Must contains only characters between [a-z] and [0-9] and start with a letter"),
		'#size' => 30,
		//'#required' => TRUE,
		);
	//
	$form['field_type_val'] = array(
		'#type' => "values" , 
		'#value' => array(t("Text field") , t("Radio button"), t("Dropdown Select"), t("Check boxes"), t("Textarea"))
		);
	$form["field_type"] = array(
		'#type' => "radios", 
		'#title' => t("Field type : "),
		'#description' => t("Select the field type"),
		'#options' => drupal_map_assoc($form['field_type_val']['#value']),
		//'#required' => TRUE,
		);

	/** Text field*/
	$form['text_field'] = array(
		'#type' => 'fieldset',
		'#title' => t("Text field properties"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Text field')),
				),
			),
		);
	$form['text_field']["maxlenght"] = array(
		'#type' => "textfield",
		'#title' => t("Enter the field lenght"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Text field')),
				),
			),
		);
	/**radio button*/
	$form['field_radio'] = array(
		'#type' => 'fieldset',
		'#title' => t("Radio button properties"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Radio button')),
				),
			),
		);
	$form['field_radio']["option_values"] = array(
		'#type' => "textarea",
		'#rows' => '2',
		'#cols' => '2',
		'#resizable' => FALSE,		
		'#title' => t("Enter options value seperate by a comma, eg: red,yellow,blue"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Radio button')),
				),
			),
		//'#required' => TRUE,
		);

	/**Dropdown Select*/
	$form['field_dds'] = array(
		'#type' => 'fieldset',
		'#title' => t("Dropdown Select properties"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Dropdown Select')),
				),
			),
		);
	$form['field_dds']["option_values_dds"] = array(
		'#type' => "textarea",
		'#rows' => '2',
		'#cols' => '2',
		'#resizable' => FALSE,		
		'#title' => t("Enter options value seperate by a comma, eg: red,yellow,blue"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Dropdown Select')),
				),
			),
		//'#required' => TRUE,
		);

	/**Check boxes*/
	$form['field_cbox'] = array(
		'#type' => 'fieldset',
		'#title' => t("Check boxes properties"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Check boxes')),
				),
			),
		);
	$form['field_cbox']["option_values_cbox"] = array(
		'#type' => "textarea",
		'#rows' => '2',
		'#cols' => '2',
		'#resizable' => FALSE,
		'#title' => t("Enter options value seperate by a comma, eg: red,yellow,blue"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Check boxes')),
				),
			),
		//'#required' => TRUE,
		);

	/** Textarea field*/
	$form['field_tarea'] = array(
		'#type' => 'fieldset',
		'#title' => t("Textarea properties"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Textarea')),
				),
			),
		);
	$form['field_tarea']["rows"] = array(
		'#type' => "textfield",
		'#title' => t("Number of rows"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Textarea')),
				),
			),
		);
	$form['field_tarea']["cols"] = array(
		'#type' => "textfield",
		'#title' => t("Number of cols"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Textarea')),
				),
			),
		);
	//
	$form['field_description'] = array(
		'#type' => "textarea",
		'#title' => t("Description (optional) : "),
		'#description' => t("Enter the a description for this field"),
		'#rows' => 8,
		'#cols' => 8,
		'#resizable' => FALSE
		);
	
	$form['submit'] = array( 
		'#type' => 'submit', 
		'#value' => t('Create field'), 
		);
	
    $form['#submit'][] = 'membership_admin_settings_submit';
    
    return $form;//system_settings_form($form);    
}

/**
 **** membership_admin_settings_submit
 */
function membership_admin_settings_submit($form, &$form_state) {
	//$schema['jl_signupfields']
	$field_label_name = $form_state['values']['field_label_name'];
	$field_id_name = $form_state['values']['field_id_name'];
	$field_type = $form_state['values']['field_type'];
	$field_description = $form_state['values']['field_description'];
	$field = array(
		'type' => 'varchar',
		'length' => "200",
		'not null' => TRUE,
		'default' => '',
		'initial' => '', // Sets initial value for preexisting nodes.
		'description' => $field_description,
		);
		// Create a regular index called 'marked' on the field named 'marked'.
	/*$keys['indexes'] = array(
		$field_id_name => array('')
	);*/
	$keys = array(); 
	if(db_add_field('jl_user_infos', $field_id_name, $field, $keys)){
		form_set_error("field_label_name", t("Sorry unable to create the field"));
	} 
	else
		$nid = db_insert('jl_signupfields')->fields(array(
		      'field_label' => $field_label_name,
		      'field_iden' => $field_id_name,
		      'field_type' => $field_type,
		      'field_desc' => $field_description,
		      'field_option' => $form_state["field_option"],
		      'actif_signup' => 1,
		      'actif_profile' => 0,
		      'actif_order' => 0,
		      'created' => time(),
		      'updated' => time(),
		    ))->execute();
		db_update('jl_signupfields') 
	    ->fields(array( 'field_weight' => $nid, )) 
	    ->condition('field_id', $nid, '=') 
	    ->execute();


}

/**
 *
 **** membership_admin_settings_validate
 */
function membership_admin_settings_validate($form, &$form_state) {

	$field_label_name = $form_state['values']['field_label_name'];
	$field_id_name = $form_state['values']['field_id_name'];
	$field_type = $form_state['values']['field_type'];

	if(empty($field_label_name))
		form_set_error("field_label_name", t("The label name is required"));
	if(empty($field_id_name))
		form_set_error("field_id_name", t("The field ID is required"));
	if(empty($field_type))
		form_set_error("field_type", t("Select the field type"));

	switch($field_type) {

		case 'Radio button'://  
			$option_values = $form_state['values']['option_values'];
			
			if(empty($option_values))
				form_set_error("option_values", t("Radio buttons options value is required"));
			else
				$form_state["field_option"] = $option_values;
			break;
		case  'Dropdown Select':
			$option_values_dds = $form_state['values']['option_values_dds'];
			
			if(empty($option_values_dds))
				form_set_error("option_values_dds", t("Dropdown Select options value is required"));
			else
				$form_state["field_option"] = $option_values_dds;

			break;
		case 'Check boxes':
			$option_values_cbox = $form_state['values']['option_values_cbox'];
			
			if(empty($option_values_cbox))
				form_set_error("option_values_cbox", t("Check boxes options value is required"));
			else
				$form_state["field_option"] = $option_values_cbox;

			break;
	}

}