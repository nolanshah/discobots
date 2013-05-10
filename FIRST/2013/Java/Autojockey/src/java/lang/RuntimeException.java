package java.lang;

public class RuntimeException extends Exception{

    /** Constructs a new runtime exception with <code>null</code> as its
     * detail message.  The cause is not initialized.
     */
    public RuntimeException() {
        super();
    }

    /** Constructs a new runtime exception with the specified detail message.
     * The cause is not initialized.
     *
     * @param   message   the detail message. The detail message is saved for
     *          later retrieval by the getMessage() method.
     */
    public RuntimeException(String message) {
        super(message);
    }
    
    /** Constructs a new runtime exception with the specified detail message
     *  and cause.
     * 
     *
     * @param   message   the detail message. The detail message is saved for
     *          later retrieval by the getMessage() method.
     * @param cause the cause of the exception. 
     */    
    public RuntimeException(String message, Throwable cause)
    {
        super(message, cause);
    }
    
    /** Constructs a new runtime exception with the specified cause.
     *
     * @param cause the cause of the exception. 
     */    
    public RuntimeException(Throwable cause)
    {
        super(cause);
    }

}
