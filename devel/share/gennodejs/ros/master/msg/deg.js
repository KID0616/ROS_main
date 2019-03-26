// Auto-generated. Do not edit!

// (in-package master.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class deg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.deg = null;
    }
    else {
      if (initObj.hasOwnProperty('deg')) {
        this.deg = initObj.deg
      }
      else {
        this.deg = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type deg
    // Serialize message field [deg]
    bufferOffset = _serializer.uint16(obj.deg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type deg
    let len;
    let data = new deg(null);
    // Deserialize message field [deg]
    data.deg = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'master/deg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '37c3b1a681be3c306e3679e4da1932c3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint16 deg
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new deg(null);
    if (msg.deg !== undefined) {
      resolved.deg = msg.deg;
    }
    else {
      resolved.deg = 0
    }

    return resolved;
    }
};

module.exports = deg;
