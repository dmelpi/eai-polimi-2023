
# ******************************************************************************
# * @attention
# *
# * Copyright (c) 2022 STMicroelectronics.
# * All rights reserved.
# *
# * This software is licensed under terms that can be found in the LICENSE file
# * in the root directory of this software component.
# * If no LICENSE file comes with this software, it is provided AS-IS.
# *
# *
# ******************************************************************************
#


import json

class PnPLCmdField:
    def __init__(self):
        self.name
        self.value

class PnPLCMDManager:

    def __init__(self):
        pass

    # @staticmethod #OLD till HSDatalog2 v1.0.1
    # def create_get_presentation_string_cmd():
    #     message = {"system_info":""}
    #     return json.dumps(message)
    
    @staticmethod
    def create_get_presentation_string_cmd():
        message = {"get_presentation":""}
        return json.dumps(message)
    
    @staticmethod #Only for HSDatalog2 > v1.2.0
    def create_get_identity_string_cmd():
        message = {"get_identity":""}
        return json.dumps(message)

    @staticmethod
    def create_get_device_status_cmd():
        message = {"get_status":"all"}
        return json.dumps(message)
    
    @staticmethod
    def create_get_component_status_cmd(comp_name: str):
        message = {"get_status": comp_name }
        return json.dumps(message)

    @staticmethod
    def create_set_property_cmd(comp_name, prop_name, prop_value):
        message = {
            comp_name: {
                prop_name : prop_value
                }
            }
        return json.dumps(message)
    
    @staticmethod
    def create_command_cmd(comp_name: str, command_name: str, req_name: str = None, req_value = None):
        if req_name is None:
            message = {
                comp_name + "*" + command_name: ""
                }
        elif req_name is None and req_value is not None:
            message = {
                comp_name + "*" + command_name: req_value
                }
        elif req_name is not None and req_value is not None:
            message = {
            comp_name + "*" + command_name: {
                    req_name: req_value
                }
            }
        return json.dumps(message)
        