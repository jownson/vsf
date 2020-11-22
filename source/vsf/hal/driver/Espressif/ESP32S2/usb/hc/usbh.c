/*****************************************************************************
 *   Copyright(C)2009-2019 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

/*============================ INCLUDES ======================================*/

//#include "../../common.h"
#include "./usbh.h"

#if VSF_USE_USB_HOST == ENABLED && VSF_USBH_USE_HCD_DWCOTG == ENABLED

// for vk_dwcotg_hc_ip_info_t and USB_SPEED_XXX
#include "component/vsf_component.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

extern vsf_err_t __esp32s2_usb_init(esp32s2_usb_t *usb, vsf_arch_prio_t priority,
                usb_ip_irq_handler_t handler, void *param);

/*============================ IMPLEMENTATION ================================*/

vsf_err_t esp32s2_usbh_init(esp32s2_usb_t *hc, usb_hc_ip_cfg_t *cfg)
{
    hc->is_host = true;
    return __esp32s2_usb_init(hc, cfg->priority, cfg->irq_handler, cfg->param);
}

void esp32s2_usbh_get_info(esp32s2_usb_t *hc, usb_hc_ip_info_t *info)
{
    vk_dwcotg_hc_ip_info_t *dwcotg_info = (vk_dwcotg_hc_ip_info_t *)info;
    ASSERT(info != NULL);
    dwcotg_info->regbase = hc->param->reg;
    dwcotg_info->ep_num = esp32s2_usbh_ep_number;
    dwcotg_info->is_dma = esp32s2_usbh_ep_is_dma;
    dwcotg_info->speed = USB_SPEED_FULL;
}

void esp32s2_usbh_irq(esp32s2_usb_t *hc)
{
    VSF_HAL_ASSERT(false);
}

#endif
