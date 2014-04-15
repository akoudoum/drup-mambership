<?php
/*******************************************************
 * Copyright (C) 2014 Armel Koudoum <dev.goldprint@gmail.com>
 * 
 * This file is part of Jungle Lion.
 * 
 * Jungle Lion can not be copied and/or distributed in any way without the express
 * permission of Armel Koudoum
 *******************************************************/


function membership_signupfields_edit($form, &$form_state, $fields) {

    $form['disclaimer'] = array( 
	    '#prefix' => '<h2>', 
	    '#markup' => t('Edit field.'), 
	    '#suffix' => '</h2>', 
    ); 
	$form['field_label_name'] = array(
		'#type' => "textfield",
		'#title' => t("Field label : "),
		'#description' => t("Enter the label name of the new field"),
		'#size' => 50,
		'#default_value' => $fields->field_label,
		);
	//
	$form['field_id_name'] = array(
		'#type' => "textfield",
		'#title' => t("Field ID (Not editable): "),
		'#description' => t("Must contains only characters between [a-z] and [0-9] and start with a letter"),
		'#size' => 30,
		'#default_value' => $fields->field_iden,
		'#disabled' => true,
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
		'#default_value' => $fields->field_type
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
		'#default_value' => ($fields->field_type=='Text field' ? $fields->field_option:''),
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
		'#default_value' => ($fields->field_type=='Radio button' ? $fields->field_option:''),
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
		'#default_value' => ($fields->field_type=='Dropdown Select' ? $fields->field_option:''),
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
		'#default_value' => ($fields->field_type=='Check boxes' ? $fields->field_option:''),
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
		'#default_value' => ($fields->field_type=='Textarea' ? explode(',',$fields->field_option)[0]:''),
		);
	$form['field_tarea']["cols"] = array(
		'#type' => "textfield",
		'#title' => t("Number of cols"),
		'#states' => array (
			'visible' => array(
				':input[name="field_type"]'	=> array('value' => t('Textarea')),
				),
			),
		'#default_value' => ($fields->field_type=='Textarea' ? explode(',',$fields->field_option)[1]:''),
		);
	//
	$form['field_description'] = array(
		'#type' => "textarea",
		'#title' => t("Description (optional) : "),
		'#description' => t("Enter the a description for this field"),
		'#rows' => 8,
		'#cols' => 8,
		'#resizable' => FALSE,
		'#default_value' => $fields->field_desc,
		);
	
	$form['submit'] = array( 
		'#type' => 'submit', 
		'#value' => t('Save changes'), 
		);
	
    $form['#submit'][] = 'membership_signupfields_edit_submit';
    
    return $form;    
}

/**
 **** membership_admin_settings_submit
 */
function membership_signupfields_edit_submit($form, &$form_state) {
	//$schema['jl_signupfields']
	$field_label_name = $form_state['values']['field_label_name'];
	$field_id_name = $form_state['values']['field_id_name'];
	$field_type = $form_state['values']['field_type'];
	$field_description = $form_state['values']['field_description'];

	$nid = db_update('jl_signupfields')->fields(array(
	      'field_label' => $field_label_name,
	      //'field_iden' => $field_id_name,
	      'field_type' => $field_type,
	      'field_desc' => $field_description,
	      'field_option' => $form_state["field_option"],
	      'updated' => time(),
	    ))
		->condition('field_iden', $field_id_name, '=') 
		->execute();

}

/**
 *
 **** membership_admin_settings_validate
 */
function membership_signupfields_edit_validate($form, &$form_state) {

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