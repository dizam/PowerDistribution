        #include "QueueAr.h"

        /**
         * Construct the queue.
         */
 
        Queue::Queue( int capacity ) : theArray( capacity )
        {
            makeEmpty( );
        }

        /**
         * Test if the queue is logically empty.
         * Return true if empty, false otherwise.
         */

        bool Queue::isEmpty( ) const
        {
            return currentSize == 0;
        }

        /**
         * Test if the queue is logically full.
         * Return true if full, false otherwise.
         */

        bool Queue::isFull( ) const
        {
            return currentSize == theArray.size( );
        }

        /**
         * Make the queue logically empty.
         */

        void Queue::makeEmpty( )
        {
            currentSize = 0;
            front = 0;
            back = -1;
        }

        /**
         * Get the least recently inserted item in the queue.
         * Return the least recently inserted item in the queue
         * or throw Underflow if empty.
         */

        const int Queue::getFront( ) const
        {
            if( isEmpty( ) )
                throw Underflow( );
            return theArray[ front ];
        }

        /**
         * Return and remove the least recently inserted item from the queue.
         * Throw Underflow if empty.
         */
        int Queue::dequeue( )
        {

            currentSize--;
            int frontItem = theArray[ front ];
            increment( front );
            return frontItem;
        }

        /**
         * Insert x into the queue.
         * Throw Overflow if queue is full
         */
        void Queue::enqueue( int x )
        {
	  //           if( isFull( ) )
	  //    throw Overflow( );
	  increment(back);
            theArray[ back ] = x;
            currentSize++;
        }

        /**
         * Internal method to increment x with wraparound.
         */
        void Queue::increment( int & x )
        {
	  if (++x == theArray.size())
            x = 0;             

        }
       
int Queue::getSize() const
{
  return currentSize;
}
