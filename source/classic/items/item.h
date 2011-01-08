#ifndef OSS_CLASSIC_ITEMS_ITEM_H
#define OSS_CLASSIC_ITEMS_ITEM_H

#include "../external.h"
#include "../responder.h"

#include "../tower/tower.h"
#include "../people/person.h"


namespace OSS {
	namespace Classic {		
		class Item : public Responder {
		public:
			//Item Types
			typedef enum {
				kNoneType = 0,
				
				//Structure
				kLobbyType,
				kFloorType,
				kStairsType,
				kEscalatorType,
				
				//Elevator
				kStandardElevatorType,
				kServiceElevatorType,
				kExpressElevatorType,
				
				//Office
				kOfficeType,
				
				//Hotel
				kSingleRoomType,
				kDoubleRoomType,
				kSuiteType,
				
				//Entertainment
				kFastFoodType,
				kRestaurantType,
				kShopType,
				kCinemaType,
				kPartyHall,
				
				//Infrastructure
				kParkingRampType,
				kParkingSpaceType,
				kRecyclingCenterType,
				kMetroType,
				
				//Services
				kCathedrakType,
				kSecurityType,
				kMedicalCenterType,
				kHousekeepingType,
				
				//Condo
				kCondoType,
				
				kMaxType
			} Type;
			
			//Item Groups
			typedef enum {
				kNoneGroup = 0,
				
				kStructureGroup,
				kElevatorGroup,
				kOfficeGroup,
				kHotelGroup,
				kEntertainmentGroup,
				kInfrastructureGroup,
				kServicesGroup,
				
				kMaxGroup
			} Group;
			
			//Item Categories
			typedef enum {
				kFacilityCategory,
				kTransportCategory
			} Category;
			
			//Item Attributes
			enum {
				kFlexibleWidthAttribute		= (1 << 0),
				kEvery15thFloorAttribute	= (1 << 1),
				kNotAboveGroundAttribute	= (1 << 2),
				kNotBelowGroundAttribute	= (1 << 3),
				kAllowedOnGroundAttribute	= (1 << 4),
				kUndestructibleAttribute	= (1 << 5)
			};
			
			//Item Descriptor
			typedef struct {
				Type type;
				Group group;
				Category category;
				unsigned short minRating;
				unsigned short attributes;
				unsigned int price;
				int2 cells;
				int2 minUnit;
				rectmaski mask;
			} Descriptor;
			
			
			/**
			 * Initialization
			 */
		public:
			Item(Tower * tower, Descriptor * descriptor);
			virtual ~Item();
			
			//Note that the init() function is separate from the constructor since we want to be able
			//to initialize the entire class hierarchy of the item at once. Calling virtual methods in
			//the constructor fails.
			virtual void init();	//calls the initialization tree
			virtual void update();	//calls the update tree
			
			//Factory
			static Item * make(Tower * tower, Descriptor * descriptor);
			static Item * make(Tower * tower, Descriptor * descriptor,
							   unsigned int itemID);
			static Item * make(Tower * tower, Descriptor * descriptor,
							   unsigned int itemID, recti rect);
			
			
			/**
			 * Basic Attributes
			 */
			const Pointer<Tower> tower;
			const Descriptor * descriptor;
			Type getType();
			Group getGroup();
			Category getCategory();
			
			
			/**
			 * Identification
			 */
		private:
			unsigned int itemID;
		public:
			unsigned int getItemID() const;
			void setItemID(unsigned int itemID);
			bool isValid() const;
			
			
			/**
			 * Location
			 */
		private:
			recti rect;
			rectd worldRect;
		public:
			const recti & getRect() const;
			recti getFloorRect(int floor) const;
			void setRect(const recti & rect);
			const rectd & getWorldRect() const;
			void setWorldRect(const rectd & worldRect);
			
			//Convenience
			unsigned int getNumFloors() const;
			int getMaxFloor() const;
			int getMinFloor() const;
			
			
			/**
			 * Basic Sprites
			 */
			virtual void initBasicSprites();
			virtual void updateBasicSprites();
			
			//Backgrounds
		protected:
			std::map<unsigned int, Engine::Sprite> backgrounds;
			bool hasUnionBackground;
		public:
			virtual void initBackground();
			virtual void updateBackground();
			
			
			//Construction Process
		protected:
			Pointer<Engine::Sprite> constructionSprite;
			Pointer<Engine::Sprite> constructionWorkerSprite[3];
			double constructionWorkerUpdateTimer;
			double constructionProgress;
			bool underConstruction;
			bool drawFlexibleConstruction;
		public:
			void setUnderConstruction(bool uc);
			void updateConstructionWorkerSprites();
			
			//Descriptors
			static Descriptor * descriptorForItemType(Type itemType);
			
			//Simulation
			virtual void advance(double dt);
			
			//Drawing
			virtual void draw(rectd visibleRect);
			
			/**
			 * Notifications
			 */
			
			//Location
			virtual void onChangeLocation();
			
			//Surroundings
			virtual void onChangeTransportItems() {}
			
			//Timing
			virtual void onDateAdvance() {}
			
			
			/**
			 * People
			 */
		protected:
			typedef std::set< Pointer<Person> > People;
			People people;
		public:
			virtual void addPerson(Person * person);
			virtual void removePerson(Person * person);
		};
	}
}

//Include the various facilities
#include "facilities/hotel/singleroom.h"
#include "facilities/hotel/doubleroom.h"
#include "facilities/hotel/suite.h"
#include "facilities/hotel/housekeeping.h"
#include "facilities/office/office.h"
#include "facilities/structure/lobby.h"

//Include the various transports
#include "transports/elevators/standardelevator.h"
#include "transports/stairslike/escalator.h"
#include "transports/stairslike/stairs.h"


#endif
