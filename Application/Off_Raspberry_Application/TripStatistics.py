
class TripStatistics:
    def __init__(self):
        self.start_time = None
        self.end_time = None
        self.suddenBrake = 0
        self.suddenAcceleration = 0
        self.AggTl = 0
        self.AggTr = 0
        self.speedLimitViolation = 0
        self.normalDriving = 0
        self.overAllScore = 0

    def get_trip_statistics(self):
        return {
            "start_time": self.start_time,
            "end_time": self.end_time,
            "suddenBraking": self.suddenBrake,
            "suddenAcceleration": self.suddenAcceleration,
            "aggTL": self.AggTl,
            "aggTR": self.AggTr,
            "speedLimitViolation": self.speedLimitViolation,
            "normalDriving": self.normalDriving,
            "totalScore": self.overAllScore
        }
    
    def calculateOverAllScore ():
        return 0
    def setStart_time(self, start_time):
        self.start_time = start_time

    def setEnd_time(self, end_time):
        self.end_time = end_time
    
    def setSuddenBrake(self, suddenBrake):
        self.suddenBrake = suddenBrake
    
    def setSuddenAcceleration(self, suddenAcceleration):
        self.suddenAcceleration = suddenAcceleration
    
    def setAggTl(self, AggTl):
        self.AggTl = AggTl

    def setAggTr(self, AggTr):
        self.AggTr = AggTr
    
    def setSpeedLimitViolation(self, speedLimitViolation):
        self.speedLimitViolation = speedLimitViolation
    
    def setNormalDriving(self, normalDriving):
        self.normalDriving = normalDriving

    def setOverAllScore(self, overAllScore):
        self.overAllScore = overAllScore

    def getStart_time(self):
        return self.start_time
    
    def getEnd_time(self):
        return self.end_time
    
    def getSuddenBrake(self):
        return self.suddenBrake
    
    def getSuddenAcceleration(self):
        return self.suddenAcceleration
    
    def getAggTl(self):
        return self.AggTl
    
    def getAggTr(self):
        return self.AggTr
    
    def getSpeedLimitViolation(self):
        return self.speedLimitViolation
    
    def getNormalDriving(self):
        return self.normalDriving
    
    def getOverAllScore(self):
        return self.overAllScore
    

    def increment_sudden_brake(self):
        self.suddenBrake += 1

    def increment_sudden_acceleration(self):
        self.suddenAcceleration += 1

    def increment_agg_tl(self):
        self.AggTl += 1

    def increment_agg_tr(self):
        self.AggTr += 1

    def increment_speed_limit_violation(self):
        self.speedLimitViolation += 1

    def increment_normal_driving(self):
        self.normalDriving += 1


    
    
