jQuery(document).ready(function(){

		jQuery("#membership-admin-fieldslist .sticky-enabled.table-select-processed tbody").sortable({
    	cursor: "move",
	    update: function(event, ui) {
	    
	      var i = 1;
	      jQuery(this).find('tr').each(function(key, val){
	      		
	      		jQuery(val).find('input[type="text"').attr('value', i);
	      		if(i%2 == 1) {
	      			jQuery(this).addClass('even'); 
	      			jQuery(this).addClass('odd');
	      		} else {
	      			jQuery(this).removeClass('odd'); 
	      			jQuery(this).addClass('even');
	      		}	

	      		i++;
	      });
	      jQuery('.messages.warning.listtable').fadeIn('slow');
	     }
		});
});