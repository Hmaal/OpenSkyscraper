#ifndef OSS_CORE_APPLICATION_H
#define OSS_CORE_APPLICATION_H

#include "responder.h"

#include "../base/autoreleasequeue.h"
#include "eventpump.h"
#include "invocation.h"
#include "../base/pointer.h"


namespace OSS {
	namespace Core {
		class Application : public Responder {
			
			//The application has a basic autorelease queue in order to catch the early garbage
			Base::AutoreleaseQueue autoreleaseQueue;
			
			
			/**
			 * Types
			 */
		public:
			//Termination
			typedef enum {
				TerminateCancel = 0,
				TerminateNow,
				TerminateLater
			} TerminateReply;
			
			//Invocation Ordering
			typedef enum {
				Before	= -1,
				After	= 1
			} OrderingMode;
			
			
			/**
			 * Run Loop
			 */
		private:
			TerminateReply terminateReply;
			
		public:
			void run();			
			bool isRunning();
			
			virtual void willRun() {}
			virtual void willIterateRunLoop() {}
			virtual void didIterateRunLoop() {}
			virtual void didRun() {}
			
			void terminate();
			bool isTerminating();
			TerminateReply shouldTerminate();
			
			
			/**
			 * Invocation
			 *
			 * The invocation system provides a means of queuing function calls in the application
			 * run loop. A game engine might for example add a periodic invocation to hook into the
			 * run loop to provide timing and animation.
			 */
		private:
			typedef std::vector< Base::Pointer<AbstractInvocation> > InvocationVector;
			InvocationVector invocations;
		public:
			void addInvocation(AbstractInvocation * invocation);
			void addInvocation(AbstractInvocation * invocation, OrderingMode ordered,
							   AbstractInvocation * relativeTo);
			void removeInvocation(AbstractInvocation * invocation);
			
			void performInvocations();
			
			virtual void willPerformInvocations() {}
			virtual void didPerformInvocations() {}
			
			
			/**
			 * Events
			 */
		protected:
			Base::Pointer<EventPump> eventPump;
			
		public:
			void pumpEvents();
			
			virtual void willPumpEvents() {}
			virtual void didPumpEvents() {}
		};
	}
}


#endif
