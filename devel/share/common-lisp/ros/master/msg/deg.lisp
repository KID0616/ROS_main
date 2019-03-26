; Auto-generated. Do not edit!


(cl:in-package master-msg)


;//! \htmlinclude deg.msg.html

(cl:defclass <deg> (roslisp-msg-protocol:ros-message)
  ((deg
    :reader deg
    :initarg :deg
    :type cl:fixnum
    :initform 0))
)

(cl:defclass deg (<deg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <deg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'deg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name master-msg:<deg> is deprecated: use master-msg:deg instead.")))

(cl:ensure-generic-function 'deg-val :lambda-list '(m))
(cl:defmethod deg-val ((m <deg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader master-msg:deg-val is deprecated.  Use master-msg:deg instead.")
  (deg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <deg>) ostream)
  "Serializes a message object of type '<deg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'deg)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'deg)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <deg>) istream)
  "Deserializes a message object of type '<deg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'deg)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'deg)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<deg>)))
  "Returns string type for a message object of type '<deg>"
  "master/deg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'deg)))
  "Returns string type for a message object of type 'deg"
  "master/deg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<deg>)))
  "Returns md5sum for a message object of type '<deg>"
  "37c3b1a681be3c306e3679e4da1932c3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'deg)))
  "Returns md5sum for a message object of type 'deg"
  "37c3b1a681be3c306e3679e4da1932c3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<deg>)))
  "Returns full string definition for message of type '<deg>"
  (cl:format cl:nil "uint16 deg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'deg)))
  "Returns full string definition for message of type 'deg"
  (cl:format cl:nil "uint16 deg~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <deg>))
  (cl:+ 0
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <deg>))
  "Converts a ROS message object to a list"
  (cl:list 'deg
    (cl:cons ':deg (deg msg))
))
