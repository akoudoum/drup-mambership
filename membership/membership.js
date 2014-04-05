jQuery(document).ready(function(){
		var startPosition;
		var endPosition;
		jQuery("#membership-admin-fieldslist .sticky-enabled.table-select-processed tbody").sortable({
    	cursor: "move",
	    start:function(event, ui){
	      startPosition = ui.item.prevAll().length + 1;
	    },
	    update: function(event, ui) {
	      endPosition = ui.item.prevAll().length + 1;

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
	     }
		});
});