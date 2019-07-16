/*
 * uMTP Responder
 * Copyright (c) 2018 - 2019 Viveris Technologies
 *
 * uMTP Responder is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * uMTP Responder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 3 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with uMTP Responder; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file   mtp_properties.c
 * @brief  MTP properties datasets helpers
 * @author Jean-Fran�ois DEL NERO <Jean-Francois.DELNERO@viveris.fr>
 */

#include <stdint.h>
#include <stdio.h>

#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/statvfs.h>

#include <time.h>

#include "logs_out.h"

#include "mtp_helpers.h"

#include "fs_handles_db.h"

#include "mtp.h"
#include "mtp_datasets.h"
#include "mtp_properties.h"

#include "usb_gadget_fct.h"

#include "mtp_constant.h"
#include "mtp_constant_strings.h"

#include "mtp_support_def.h"

int build_properties_dataset(mtp_ctx * ctx,void * buffer, int maxsize,uint32_t property_id,uint32_t format_id)
{
	int ofs;

	ofs = 0;

	PRINT_DEBUG("build_properties_dataset : 0x%.4X (%s) (Format : 0x%.4X - %s )", property_id, mtp_get_property_string(property_id), format_id, mtp_get_format_string(format_id));

	switch(property_id)
	{
		case MTP_PROPERTY_OBJECT_FILE_NAME:
			poke(buffer, &ofs, 2, MTP_PROPERTY_OBJECT_FILE_NAME);      // PropertyCode
			poke(buffer, &ofs, 2, MTP_TYPE_STR);                       // DataType
			poke(buffer, &ofs, 1, 0x01);                               // Get/Set
			poke(buffer, &ofs, 1, 0x00);                               // DefaultValue : Null sized strcat
			poke(buffer, &ofs, 4, 0x0000000);                          // GroupCode
			poke(buffer, &ofs, 1, 0x00);                               // FormFlag : None
		break;
	}

	return ofs;
}
