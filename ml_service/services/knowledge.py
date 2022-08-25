import logging


logger = logging.getLogger("ml_service")

class Knowledge():
    def __init__(self):
        self.mode = None  # either None, "specific", "local", "global"
        self.type = "similar"  # also possible: "predicted", 
        self.scope = []  # knowledge tags
        self.kb_location = None  # location of the knowledge base
        self.parameters = None #dict() with unnormalised Theta
        self.confidence = None
        self.uuid = None
        self.prediction = False  # bool, wether this knowledge was predicted or not
        self.prediction_error = None
        self.identity = [1]  # task identity
        self.skill_class = None
        self.source = []  # uuid(s) of the source ml_results
        self.expected_cost = None
        self.time = None
        self.tags = []  #actual tags of the knowledge itself
        self.equal_start = False  # if True the svm.py will use the same first batch (from equal_tags) every time
        self.equal_tags = []
        self.cost_function = []

    def to_dict(self):
        meta_information = {
            "mode": self.mode,
            "type": self.type,
            "scope": self.scope,
            "kb_location": self.kb_location,
            "confidence": self.confidence,
            "uuid": self.uuid,
            "prediction": self.prediction,
            "prediction_error": self.prediction_error,
            "identity": self.identity,
            "skill_class": self.skill_class,
            "source": self.source,
            "expected_cost": self.expected_cost,
            "time": self.time,
            "tags": self.tags,
            "equal_start": self.equal_start,
            "equal_tags": self.equal_tags,
            "cost_function": self.cost_function
        }
        knowledge_dict = {
            "parameters": self.parameters,
            "meta": meta_information
        }
        return knowledge_dict
    
    def from_dict(self, input: dict):
        self.parameters = input.get("parameters", None)
        if "meta" not in input:
            self.mode = input.get("mode", None)
            self.type = input.get("type", "similar")
            self.scope = input.get("scope", [])
            self.kb_location = input.get("kb_location", None)
            self.confidence = input.get("confidence", None)
            self.uuid = input.get("uuid", None)
            self.prediction = input.get("prediction", False)
            self.prediction_error = input.get("prediction_error", False)
            self.identity = input.get("identity", [1])
            self.skill_class = input.get("skill_class", None)
            self.source = input.get("source", [])
            self.expected_cost = input.get("expected_cost", None)
            self.time = input.get("time", None)
            self.tags = input.get("tags", [])
            self.tags.extend(input.get("kb_tags", []))  # dont use kb_tags anymore
            self.equal_tags = input.get("equal_tags", [])
            self.equal_start = input.get("equal_start", False)
            self.cost_function = input.get("cost_function", [])
        else:
            input = input["meta"]
            self.mode = input.get("mode", None)
            self.type = input.get("type", "similar")
            self.scope = input.get("scope", [])
            self.kb_location = input.get("kb_location", None)
            self.confidence = input.get("confidence", None)
            self.uuid = input.get("uuid", None)
            self.prediction = input.get("prediction", False)
            self.prediction_error = input.get("prediction_error", False)
            self.identity = input.get("identity", [1])
            self.skill_class = input.get("skill_class", None)
            self.source = input.get("source", [])
            self.expected_cost = input.get("expected_cost", None)
            self.time = input.get("time", None)
            self.tags = input.get("tags", [])
            self.tags.extend(input.get("kb_tags", []))  # dont use kb_tags anymore
            self.equal_tags = input.get("equal_tags", [])
            self.equal_start = input.get("equal_start", False)
            self.cost_function = input.get("cost_function", [])

    def check_consistency(self):
        if self.mode == "global":
            if type(self.kb_location) != str:
                logger.error("knowledge mode is \""+self.mode+"\" but no kb_location was set.")
        if self.mode == "global" or self.mode == "local":
            if self.type is None:
                logger.error("knowledge mode is \""+self.mode+"\" but knowledge type was not set. Default is local")
        if (self.equal_start and (type(self.kb_location) != str)) or (self.equal_start and not self.equal_tags):
            logger.error("All agents should start with the same batch (equal start is True), but no location or tags are specified")





