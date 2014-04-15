<?php
/*******************************************************
 * Copyright (C) 2014 Armel Koudoum <dev.goldprint@gmail.com>
 * 
 * This file is part of Jungle Lion.
 * 
 * Jungle Lion can not be copied and/or distributed in any way without the express
 * permission of Armel Koudoum
 *******************************************************/
class CCategory {

	public static function install() {
		node_types_rebuild(); 

		foreach (self::jl_catalog_category_installed_fields() as $field) { 
			field_create_field($field); 
		} 
		// Create all the instances for our fields. 
		foreach (self::jl_catalog_category_installed_instances() as $instance) { 
			$instance['entity_type'] = 'node'; 
			$instance['bundle'] = 'jl_prod_category'; 
			field_create_instance($instance); 
		}

	}

	public static function uninstall() {
	   // Gather all the example content that might have been created while this 
	    // module was enabled. 
	    $sql = 'SELECT nid FROM {node} n WHERE n.type = :type'; 
	    $result = db_query($sql, array(':type' => 'jl_prod_category')); 
	    $nids = array(); 
	    foreach ($result as $row) { 
	    	$nids[] = $row->nid; 
	    } 
	    // Delete all the nodes at once 
	    node_delete_multiple($nids); 
	    // Loop over each of the fields defined by this module and delete 
	    // all instances of the field, their data, and the field itself. 
	    foreach (array_keys(self::jl_catalog_category_installed_fields()) as $field) { 
	    	field_delete_field($field); 
	    } 
	    // Loop over any remaining field instances attached to the job_post 
	    // content type (such as the body field) and delete them individually. 
	    $instances = field_info_instances('node', 'jl_prod_category'); 
	    foreach ($instances as $instance_name => $instance) { 
	    	field_delete_instance($instance); 
	    } 
	    // Delete our content type 
	    node_type_delete('jl_prod_category'); 
	    // Purge all field infromation 
	    field_purge_batch(1000);
	}

	private static function jl_catalog_category_installed_fields() { 
		$t = get_t(); 
		return array( 
			'jl_prod_category_name' => array( 
				'field_name' => 'jl_prod_category_name', 
				'label' => $t('Product category name'), 
				'type' => 'text', 
				), 
			'jl_prod_category_parent' => array( 
				'field_name' => 'jl_prod_category_parent', 
				'label' => $t('Parent  category'), 
				'type' => 'list_text', 
				),
			'jl_prod_category_active' => array( 
				'field_name' => 'jl_prod_category_active', 
				'label' => $t('This category is active'), 
				'type' => 'list_boolean', 
				), 
			'jl_prod_category_shortdesc' => array( 
				'field_name' => 'jl_prod_category_shortdesc', 
				'label' => $t('Description'), 
				'type' => 'text_long', 
				), 
	
			); 
	} 
	/** 
	* Return a structured array defining the field instances associated with this content type. 
	*/ 
	private static function jl_catalog_category_installed_instances() { 
		$t = get_t(); 
		return array( 
			'jl_prod_category_name' => array( 
				'field_name' => 'jl_prod_category_name', 
				'type' => 'text', 
				'label' => $t('Enter the category name'), 
				'widget' => array( 
					'type' => 'text_textfield', 
					), 
				'display' =>  array(
            		'default' => array(),
       			), 
			), 
			'jl_prod_category_parent' => array(
				'field_name' => 'jl_prod_category_parent', 
				'type' => 'list_text', 
				'label' => $t('Category parent'), 
				'widget' => array( 
					'type' => 'options_select', 
					), 
				'display' =>  array(
            		'default' => array(),
       			), 				
			),
			'jl_prod_category_active' => array(
				'field_name' => 'jl_prod_category_active', 
				'type' => 'list_boolean', 
				'label' => $t('This category is active'), 
				'widget' => array( 
					'type' => 'options_onoff', 
					), 
				'display' =>  array(
            		'default' => array(),
       			), 				
			),
			'jl_prod_category_shortdesc' => array(
				'field_name' => 'jl_prod_category_shortdesc', 
				'type' => 'text_long', 
				'label' => $t('Category description'), 
				'widget' => array( 
					'type' => 'text_textarea', 
					), 
				'display' =>  array(
            		'default' => array(),
       			), 				
			),
		); 
	}


}