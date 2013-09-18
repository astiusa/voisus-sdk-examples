using System;

namespace VoisusCS
{
    [Serializable()]
    public class VRCCException : System.Exception
    {
        public VRCCException() : base() { }
        public VRCCException(string message) : base(message) { }
        public VRCCException(string message, System.Exception inner) : base(message, inner) { }

        // A constructor is needed for serialization when an 
        // exception propagates from a remoting server to the client.  
        protected VRCCException(System.Runtime.Serialization.SerializationInfo info,
            System.Runtime.Serialization.StreamingContext context) { }
    }
}
