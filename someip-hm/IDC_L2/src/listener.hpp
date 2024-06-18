#ifndef __aclistener_HPP__
#define __aclistener_HPP__
#include <iostream>
#include <stdint.h>
#include <vector>
class Listener {
public:
  typedef struct LocationInfoStruct {
    uint8_t _Loc_Con_lane;
    float _Loc_head_right;
    float _Loc_head_left;
    float _Loc_heading_Con;
    uint64_t _Loc_TimeStamp;
    uint8_t _Loc_current_lane;
    float _Loc_speed;
    float _Loc_Altitude_pos_Con;
    uint32_t _Loc_lateral_pos;
    int64_t _Loc_Altitude_pos;
    float _Loc_speed_Con;
    float _Loc_heading;
    float _Loc_dis_left;
    float _Loc_dis_right;
    uint32_t _Loc_longitudinal_pos;
  } LocationInfoStruct;
  typedef struct OBJInfoStruct {
    uint8_t _OBJ_ID;
    uint8_t _OBJ_Type;
    float _OBJ_Hight;
    float _OBJ_HeadingAngle;
    float _OBJ_DX;
    float _OBJ_DY;
    float _OBJ_ExistProb;
    uint32_t _OBJ_Age;
  } OBJInfoStruct;
  typedef std::vector<OBJInfoStruct> OBJInfoStructArray;
  typedef struct OBJ_DispProperty_Type {
    uint8_t _OBJ_ID;
    uint8_t _ObjBarDisp;
  } OBJ_DispProperty_Type;
  typedef struct OBJ_DispProperty {
    OBJ_DispProperty_Type _Target_Obj;
    OBJ_DispProperty_Type _Left_Target_Obj;
    OBJ_DispProperty_Type _Right_Target_Obj;
    OBJ_DispProperty_Type _Target_Obj_2;
    OBJ_DispProperty_Type _Left_Target_Obj_2;
    OBJ_DispProperty_Type _Right_Target_Obj_2;
    OBJ_DispProperty_Type _Target_Obj_3;
    OBJ_DispProperty_Type _Left_Target_Obj_3;
    OBJ_DispProperty_Type _Right_Target_Obj_3;
  } OBJ_DispProperty;
  typedef struct OBJPptyInfoStruct {
    uint64_t _OBJ_TimeStamp;
    OBJInfoStructArray _OBJInfoStructArray;
    OBJ_DispProperty _OBJ_DispProperty;
  } OBJPptyInfoStruct;

public:
  Listener() {}
  virtual ~Listener() {}
  virtual void LocationInfoStructOnChange(LocationInfoStruct &value);
  virtual void OBJPptyInfoStructOnChange(OBJPptyInfoStruct &value);
};
#endif
