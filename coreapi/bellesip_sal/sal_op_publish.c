/*
linphone
Copyright (C) 2012  Belledonne Communications, Grenoble, France

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "sal_impl.h"


static void publish_refresher_listener ( const belle_sip_refresher_t* refresher
		,void* user_pointer
		,unsigned int status_code
		,const char* reason_phrase) {
	SalOp* op = (SalOp*)user_pointer;
	/*belle_sip_response_t* response=belle_sip_transaction_get_response(BELLE_SIP_TRANSACTION(belle_sip_refresher_get_transaction(refresher)));*/
	ms_message("Publish refresher  [%i] reason [%s] for proxy [%s]",status_code,reason_phrase,sal_op_get_proxy(op));


}
/*presence publish */
int sal_publish(SalOp *op, const char *from, const char *to, SalPresenceStatus status){
	belle_sip_request_t *req=NULL;
	if (from)
		sal_op_set_from(op,from);
	if (to)
		sal_op_set_to(op,to);

	op->type=SalOpPublish;
	req=sal_op_build_request(op,"PUBLISH");
	sal_add_presence_info(BELLE_SIP_MESSAGE(req),status);
	return sal_op_send_and_create_refresher(op,req,600,publish_refresher_listener);

}

